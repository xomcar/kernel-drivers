#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fs.h>

static int device_amount = 1;
static int major_n = 0;
static int minor_n = 0;

module_param(device_amount, int, S_IRUGO);
module_param(major_n, int, S_IRUGO);
module_param(minor_n, int, S_IRUGO);

static dev_t dev;

static int __init hello_init(void) {
	int result;
	if (major_n) {
		dev = MKDEV(major_n, minor_n);
		result = register_chrdev_region(dev, device_amount, "draiver");
	} else {
		result = alloc_chrdev_region(&dev, minor_n, device_amount, "draiver");
		major_n = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "draiver: can't get major %d\n", major_n);
		return result;
	}
	printk(KERN_ALERT "Got major: %d\n", major_n);
	return 0;
}

static void __exit hello_exit(void) {
	unregister_chrdev_region(dev, device_amount);
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("xomcar");
MODULE_DESCRIPTION("custom kernel module");
MODULE_ALIAS("draiver_module");
MODULE_VERSION("v0.1");
