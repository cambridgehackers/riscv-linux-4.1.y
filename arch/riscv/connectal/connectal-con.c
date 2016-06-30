#include <linux/init.h>
#include <linux/console.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/tty_driver.h>
#include <linux/irqreturn.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <asm/io.h>

#include <asm/connectal.h>

#define DRIVER_NAME "connectalcon"

#define NR_PORTS CONFIG_CONNECTAL_CONSOLE_PORTS

struct connectalcon_port {
	struct device *dev;
	struct tty_port port;
	volatile uint32_t *req_regs;
	volatile uint32_t *resp_regs;
	spinlock_t lock;
};

static struct connectalcon_port connectalcon_ports[NR_PORTS];
static DEFINE_SPINLOCK(connectalcon_ports_lock);

static void connectalcon_port_destruct(struct tty_port *port)
{
	struct connectalcon_port *p;
	unsigned long flags;

	p = container_of(port, struct connectalcon_port, port);
	spin_lock(&connectalcon_ports_lock);
	spin_lock_irqsave(&p->lock, flags);
	p->dev = NULL;
	spin_unlock_irqrestore(&p->lock, flags);
	spin_unlock(&connectalcon_ports_lock);
}

static const struct tty_port_operations connectalcon_port_ops = {
	.destruct = connectalcon_port_destruct,
};


static inline struct connectal_device *connectalcon_port_connectaldev(
	const struct connectalcon_port *port)
{
	return to_connectal_dev(port->dev->parent);
}

static struct connectalcon_port *connectalcon_port_get(unsigned int minor)
{
	struct connectalcon_port *port;

	if (unlikely(WARN_ON(minor >= NR_PORTS)))
		return NULL;

	port = NULL;
	spin_lock(&connectalcon_ports_lock);
	if (connectalcon_ports[minor].dev != NULL) {
		port = &connectalcon_ports[minor];
		tty_port_get(&port->port);
	}
	spin_unlock(&connectalcon_ports_lock);
	return port;
}

static void connectalcon_port_put(struct connectalcon_port *port)
{
	tty_port_put(&port->port);
}

static int connectal_tty_install(struct tty_driver *driver, struct tty_struct *tty)
{
	struct connectalcon_port *port;
	int ret;

	port = connectalcon_port_get(tty->index);
	if (port == NULL)
		return -ENODEV;

	if (port->req_regs == 0) {
		port->req_regs = ioremap(0xc0003000, 0x1000);
		//port->resp_regs = ioremap(0xc0003000, 0x1000);
	}

	ret = tty_standard_install(driver, tty);
	if (likely(!ret)) {
		tty->driver_data = port;
	} else {
		connectalcon_port_put(port);
	}
	return ret;
}

static int connectal_tty_open(struct tty_struct *tty, struct file *filp)
{
	struct connectalcon_port *port = tty->driver_data;

	return tty_port_open(&port->port, tty, filp);
}

static void connectal_tty_close(struct tty_struct *tty, struct file *filp)
{
	struct connectalcon_port *port = tty->driver_data;

	tty_port_close(&port->port, tty, filp);
}

static void connectal_tty_cleanup(struct tty_struct *tty)
{
	struct connectalcon_port *port = tty->driver_data;

	tty_port_put(&port->port);
	tty->driver_data = NULL;
}

static inline void connectalcon_put_char(struct connectalcon_port *port,
	unsigned int id, unsigned char ch)
{
	//while (port->req_regs[9] == 0)
	//	/* wait for not busy */;
	port->req_regs[8] = ch;
}

static int connectal_tty_write(struct tty_struct *tty,
	const unsigned char *buf, int count)
{
	struct connectalcon_port *port = tty->driver_data;
	const unsigned char *end;
	unsigned int id;

	id = connectalcon_port_connectaldev(port)->index;
	for (end = buf + count; buf < end; buf++) {
		connectalcon_put_char(port, id, *buf);
	}
	return count;
}

static int connectal_tty_write_room(struct tty_struct *tty)
{
	return 1024; /* arbitrary */
}

static void connectal_tty_hangup(struct tty_struct *tty)
{
	struct connectalcon_port *port = tty->driver_data;

	tty_port_hangup(&port->port);
}

static const struct tty_operations connectal_tty_ops = {
	.install	= connectal_tty_install,
	.open		= connectal_tty_open,
	.close		= connectal_tty_close,
	.cleanup	= connectal_tty_cleanup,
	.write		= connectal_tty_write,
	.write_room	= connectal_tty_write_room,
	.hangup		= connectal_tty_hangup,
};

static struct tty_driver *connectal_tty_driver;

static irqreturn_t connectalcon_isr(struct connectal_device *dev, sbi_device_message *msg)
{
	struct connectalcon_port *port = dev_get_drvdata(&dev->dev);

	if (msg->cmd == CONNECTAL_CMD_READ) {
		spin_lock(&port->lock);
		tty_insert_flip_char(&port->port, msg->data, TTY_NORMAL);
		tty_flip_buffer_push(&port->port);
		spin_unlock(&port->lock);

		/* Request next character */
		//FIXME 
	} else if (msg->cmd == CONNECTAL_CMD_WRITE) {
		msg->data = 0;
	} else {
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}

static int connectalcon_port_init(struct connectal_device *dev)
{
	struct connectalcon_port *port;
	unsigned int minor;
	int ret;

	ret = -EBUSY;
	port = connectalcon_ports;
	spin_lock(&connectalcon_ports_lock);
	for (minor = 0; minor < NR_PORTS; minor++, port++) {
		struct device *tty_dev;

		if (port->dev != NULL)
			continue;

		tty_port_init(&port->port);
		port->port.ops = &connectalcon_port_ops;
		spin_lock_init(&port->lock);

		tty_dev = tty_port_register_device(&port->port,
			connectal_tty_driver, minor, &dev->dev);
		if (unlikely(IS_ERR(tty_dev))) {
			ret = PTR_ERR(tty_dev);
		} else {
			port->dev = tty_dev;
			dev_set_drvdata(&dev->dev, port);
			ret = 0;
		}
	}
	spin_unlock(&connectalcon_ports_lock);
	return ret;
}

static void connectal_console_init_late(void);

static int connectalcon_probe(struct device *dev)
{
	struct connectal_device *connectal_dev;
	struct connectalcon_port *port;
	int ret;

	dev_info(dev, "detected console\n");
	connectal_dev = to_connectal_dev(dev);

	ret = connectalcon_port_init(connectal_dev);
	if (unlikely(ret))
		return ret;

	ret = connectal_request_irq(connectal_dev, connectalcon_isr);
	if (unlikely(ret))
		return ret;

	connectal_console_init_late();

	/* Request next character */
	//FIXME
	return 0;
}

static struct connectal_driver connectalcon_driver = {
	.type = "bcd",
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.probe = connectalcon_probe,
	},
};

static int __init connectalcon_init(void)
{
	int ret;

	connectal_tty_driver = tty_alloc_driver(NR_PORTS,
		TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV);
	if (unlikely(IS_ERR(connectal_tty_driver)))
		return PTR_ERR(connectal_tty_driver);

	connectal_tty_driver->driver_name = "connectal_tty";
	connectal_tty_driver->name = "ttyCONNECTAL";
	connectal_tty_driver->major = TTY_MAJOR;
	connectal_tty_driver->minor_start = 0;
	connectal_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	connectal_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	connectal_tty_driver->init_termios = tty_std_termios;
	tty_set_operations(connectal_tty_driver, &connectal_tty_ops);

	ret = tty_register_driver(connectal_tty_driver);
	if (unlikely(ret))
		goto out_tty_put;

	ret = connectal_register_driver(&connectalcon_driver);
	if (unlikely(ret))
		goto out_tty_unregister;

	return 0;

out_tty_unregister:
	tty_unregister_driver(connectal_tty_driver);
out_tty_put:
	put_tty_driver(connectal_tty_driver);
	return ret;
}

static void __exit connectalcon_exit(void)
{
	connectal_unregister_driver(&connectalcon_driver);
	tty_unregister_driver(connectal_tty_driver);
	put_tty_driver(connectal_tty_driver);
}

module_init(connectalcon_init);
module_exit(connectalcon_exit);

MODULE_DESCRIPTION("CONNECTAL console driver");
MODULE_LICENSE("GPL");


static void connectal_console_write(struct console *co, const char *buf, unsigned n)
{
	for ( ; n > 0; n--, buf++) {
		if (*buf == '\n')
			sbi_console_putchar('\r');
		sbi_console_putchar(*buf);
	}
}

static struct tty_driver *connectal_console_device(struct console *co, int *index)
{
	*index = co->index;
	return connectal_tty_driver;
}

static int __init connectal_console_setup(struct console *co, char *options)
{
	return (co->index < 0 || co->index >= NR_PORTS
		|| connectalcon_ports[co->index].dev == NULL) ?
		-ENODEV : 0;
}

static struct console connectal_console = {
	.name	= "connectalcon",
	.write	= connectal_console_write,
	.device = connectal_console_device,
	.setup	= connectal_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1
};

/*
 * Early console initialization will fail in the typical case when setup
 * precedes driver initialization.  Note that the driver will later
 * re-attempt to register the console when probing the device.
 */
static int __init connectal_console_init(void)
{
	register_console(&connectal_console);
	return 0;
}
console_initcall(connectal_console_init);

static inline void connectal_console_init_late(void)
{
	if (!(connectal_console.flags & CON_ENABLED)) {
		register_console(&connectal_console);
	}
}
