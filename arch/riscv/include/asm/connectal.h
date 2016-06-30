#ifndef _ASM_RISCV_CONNECTAL_H
#define _ASM_RISCV_CONNECTAL_H

#include <linux/device.h>
#include <linux/irqreturn.h>

#include <asm/csr.h>
#include <asm/sbi.h>

#define CONNECTAL_CMD_READ       (0x00UL)
#define CONNECTAL_CMD_WRITE      (0x01UL)
#define CONNECTAL_CMD_IDENTIFY   (0xFFUL)

#define CONNECTAL_MAX_DEV        (256)
#define CONNECTAL_MAX_ID         (64)

#define CONNECTAL_ALIGN          (64)

extern struct bus_type connectal_bus_type;

static inline void connectal_tohost(sbi_device_message *message)
{
	sbi_send_device_request(__pa(message));
}

static inline sbi_device_message *connectal_fromhost(void)
{
	uintptr_t response;
	while ((response = sbi_receive_device_response()) == 0) {
		cpu_relax();
	}
	return __va(response);
}

struct connectal_device {
	struct device dev;
	unsigned int index;
	char id[];
};

#define to_connectal_dev(d) container_of(d, struct connectal_device, dev)

struct connectal_driver {
	struct device_driver driver;
	const char *type;
};

#define to_connectal_driver(d) container_of(d, struct connectal_driver, driver)

extern int connectal_register_driver(struct connectal_driver *drv);
extern void connectal_unregister_driver(struct connectal_driver *drv);

typedef irqreturn_t (*connectal_irq_handler_t)(struct connectal_device *,
                                          sbi_device_message *);

extern int connectal_request_irq(struct connectal_device *dev, connectal_irq_handler_t handler);
extern void connectal_free_irq(struct connectal_device *dev);

#endif /* _ASM_RISCV_CONNECTAL_H */
