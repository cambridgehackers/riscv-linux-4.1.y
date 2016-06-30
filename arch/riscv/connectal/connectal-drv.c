#include <linux/device.h>
#include <linux/export.h>
#include <linux/string.h>

#include <asm/connectal.h>

int connectal_register_driver(struct connectal_driver *drv)
{
	drv->driver.bus = &connectal_bus_type;
	return driver_register(&drv->driver);
}
EXPORT_SYMBOL(connectal_register_driver);

void connectal_unregister_driver(struct connectal_driver *drv)
{
	driver_unregister(&drv->driver);
}
EXPORT_SYMBOL(connectal_unregister_driver);

static int connectal_bus_match(struct device *dev, struct device_driver *drv)
{
	const char *id;
	const char *s;
	size_t n;

	id = to_connectal_dev(dev)->id;
	s = strnchr(id, CONNECTAL_MAX_ID, ' ');
	n = (s != NULL) ? (s - id) : CONNECTAL_MAX_ID;
	return !strncmp(id, to_connectal_driver(drv)->type, n);
}

struct bus_type connectal_bus_type = {
	.name = "connectal",
	.match = connectal_bus_match,
};
EXPORT_SYMBOL(connectal_bus_type);

static int __init connectal_driver_init(void)
{
	return bus_register(&connectal_bus_type);
}
postcore_initcall(connectal_driver_init);
