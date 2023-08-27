#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "overflow_driver"
#define IOCTL_TRIGGER_OVERFLOW _IO('o', 1)

MODULE_LICENSE("GPL");

static int major_number;
static struct class *driver_class;
static struct device *driver_device;

static int mydriver_open(struct inode *inode, struct file *file)
{
    pr_info("Device opened\n");
    return 0;
}

static long mydriver_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int size;

    switch (cmd) {
        case IOCTL_TRIGGER_OVERFLOW:
            if (copy_from_user(&size, (int *)arg, sizeof(int))) {
                pr_err("Failed to copy user data\n");
                return -EFAULT;
            }

            // Vulnerability: Integer overflow
            int result = size * sizeof(int);

            pr_info("User input: %d\n", size);
            pr_info("Result of size * sizeof(int): %d\n", result);
            break;
        // Other cases...
    }

    return 0;
}

static struct file_operations fops = {
    .open = mydriver_open,
    .unlocked_ioctl = mydriver_ioctl,
};

static int __init mydriver_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        pr_err("Failed to register a major number\n");
        return major_number;
    }

    driver_class = class_create(THIS_MODULE, "overflow_driver_class");
    if (IS_ERR(driver_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("Failed to create a device class\n");
        return PTR_ERR(driver_class);
    }

    driver_device = device_create(driver_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(driver_device)) {
        class_destroy(driver_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("Failed to create a device\n");
        return PTR_ERR(driver_device);
    }

    pr_info("Driver initialized\n");
    return 0;
}

static void __exit mydriver_exit(void)
{
    device_destroy(driver_class, MKDEV(major_number, 0));
    class_unregister(driver_class);
    class_destroy(driver_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    pr_info("Driver exited\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

