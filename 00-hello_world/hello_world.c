#include "linux/module.h"
#include "linux/init.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My first kernel driver");
MODULE_AUTHOR("xomcar");

static __init int driver_init(void)
{
	printk("Kernel module loaded correctly!\n");
	return 0;
}

static __exit void driver_release(void)
{
	printk("Kernel module unloaded correctly!\n");
}

module_init(driver_init);
module_exit(driver_release);
