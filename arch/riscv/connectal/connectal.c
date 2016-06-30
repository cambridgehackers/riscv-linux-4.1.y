#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/export.h>

#include <asm/connectal.h>

struct connectal_desc {
	struct connectal_device *dev;
	connectal_irq_handler_t handler;
};

struct connectal_bus {
	struct device dev;
	struct connectal_desc *desc;
	unsigned int count;
};

static struct connectal_bus bus = {
	.desc = NULL,
	.count = 0,
};
static DEFINE_SPINLOCK(bus_lock);

int connectal_request_irq(struct connectal_device *dev, connectal_irq_handler_t handler)
{
	int ret = -EINVAL;

	if (!WARN_ON(dev->index >= bus.count)) {
		struct connectal_desc *desc;
		unsigned long flags;

		desc = bus.desc + dev->index;
		spin_lock_irqsave(&bus_lock, flags);
		if (!WARN_ON(desc->dev != dev)) {
			desc->handler = handler;
			ret = 0;
		}
		spin_unlock_irqrestore(&bus_lock, flags);
	}

	return ret;
}
EXPORT_SYMBOL(connectal_request_irq);

void connectal_free_irq(struct connectal_device *dev)
{
	connectal_request_irq(dev, NULL);
}
EXPORT_SYMBOL(connectal_free_irq);

static irqreturn_t connectal_isr(int irq, void *dev_id)
{
	irqreturn_t ret = IRQ_NONE;
	uintptr_t message_paddr;

	printk("%s:%d\n", __FUNCTION__, __LINE__);
	while ((message_paddr = sbi_receive_device_response()) != 0) {
		sbi_device_message *message;
		struct connectal_desc *desc;
		struct connectal_device *dev;
		connectal_irq_handler_t handler;

		message = __va(message_paddr);
		desc = bus.desc + message->dev;
		handler = NULL;

		spin_lock(&bus_lock);
		if (!WARN_ON(message->dev >= bus.count)) {
			dev = desc->dev;
			handler = desc->handler;
		}
		spin_unlock(&bus_lock);

		if (likely(handler != NULL))
			ret |= handler(dev, message);
	}
	return ret;
}

static void connectal_dev_release(struct device *dev)
{
	struct connectal_device *connectal_dev = to_connectal_dev(dev);

	if (!WARN_ON(connectal_dev->index >= bus.count)) {
		struct connectal_desc *desc;
		unsigned long flags;

		desc = bus.desc + connectal_dev->index;
		spin_lock_irqsave(&bus_lock, flags);
		WARN_ON(connectal_dev != desc->dev);
		desc->dev = NULL;
		desc->handler = NULL;
		spin_unlock_irqrestore(&bus_lock, flags);
	}

	kfree(connectal_dev);
}

static int __init connectal_init(void)
{
	int status;
	unsigned int i;
	int ret;
	const char *ids[] = {
	  "disk", "bcd", 0
	};

	dev_set_name(&bus.dev, connectal_bus_type.name);
	ret = device_register(&bus.dev);
	if (unlikely(ret)) {
		dev_err(&bus.dev, "error registering bus: %d\n", ret);
		return ret;
	}

	/* Enumerate devices */
	for (i = 0; i < CONNECTAL_MAX_DEV; i++) {
		const char *id = ids[i];
		struct connectal_device *dev;
		size_t len;

		if (id == 0)
			break;

		printk("%s:%d id=%s\n", __FUNCTION__, __LINE__, id);

		len = strlen(id);
		dev = kzalloc(sizeof(struct connectal_device) + len + 1, GFP_KERNEL);
		if (unlikely(dev == NULL))
			return -ENOMEM;

		if (i >= bus.count) {
			struct connectal_desc *desc;
			unsigned int count;

			count = bus.count + 8;
			desc = krealloc(bus.desc,
				sizeof(struct connectal_desc) * count, GFP_KERNEL);
			if (unlikely(desc == NULL)) {
				kfree(dev);
				return -ENOMEM;
			}
			memset(desc + bus.count, 0, sizeof(struct connectal_desc) * 8);
			bus.desc = desc;
			bus.count = count;
		}
		bus.desc[i].dev = dev;

		memcpy(dev->id, id, len);
		dev->id[len] = '\0';
		dev->index = i;
		dev->dev.parent = &bus.dev;
		dev->dev.bus = &connectal_bus_type;
		dev->dev.release = &connectal_dev_release;
		dev_set_name(&dev->dev, "connectal%u", i);

		ret = device_register(&dev->dev);
		if (unlikely(ret)) {
			dev_err(&bus.dev, "error registering device %s: %d\n",
				dev_name(&dev->dev), ret);
			put_device(&dev->dev);
		}
	}

	status = request_irq(IRQ_SOFTWARE, connectal_isr, 0, dev_name(&bus.dev), NULL);
	printk("%s:%d request_irq status %d\n", __FUNCTION__, __LINE__, status);
	return status;
}
subsys_initcall(connectal_init);
