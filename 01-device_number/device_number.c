#include "linux/module.h"
#include "linux/init.h"
#include "linux/fs.h"
#include "linux/moduleparam.h"
#include "linux/cdev.h"

#define DRIVER_NAME "draiver"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My second kernel driver");
MODULE_AUTHOR("xomcar");
MODULE_ALIAS(DRIVER_NAME);

static int draiver_major = 0;
module_param(draiver_major, int, S_IRUGO);

static int draiver_minor = 0;
module_param(draiver_minor, int, S_IRUGO);

static int draiver_n = 1;
module_param(draiver_n, int, S_IRUGO);

static dev_t dev;
static struct cdev cdev;

static int draiver_open(struct inode *file_device, struct file* file_instance)
{
	return 0;	
}

static int draiver_close(struct inode *file_device, struct file* file_instance)
{
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = draiver_open,
	.release = draiver_close,
};

static __init int draiver_init(void)
{
	int result;
	if (draiver_major)
	{
		dev = MKDEV(draiver_major, draiver_minor);
		result = register_chrdev_region(dev, draiver_n, "draiver");
	}
	else
	{
		result = alloc_chrdev_region(&dev, draiver_minor, draiver_n, "draiver");
		draiver_major = MAJOR(dev);
		draiver_minor = MINOR(dev);
	}
	if (result < 0)
	{
		printk(KERN_WARNING "can't get major %d\n", draiver_major);
		return result;
	}

	cdev_init(&cdev, &fops);
	cdev.owner = THIS_MODULE;
	result = cdev_add(&cdev, dev, draiver_n);
	if (result < 0)
	{
		printk(KERN_NOTICE "error %d when adding draiver %d", result, draiver_n); 
		unregister_chrdev_region(dev, draiver_n);
		return result;
	}
	printk(KERN_INFO "draiver init ok %d %d", draiver_major, draiver_minor);
	return 0;
}

static __exit void draiver_release(void)
{
	unregister_chrdev_region(dev, draiver_n);
}

module_init(draiver_init);
module_exit(draiver_release);
