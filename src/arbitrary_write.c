#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "arbitrary_write_driver"
#define IOCTL_WRITE_MEMORY _IOW('a', 1, unsigned long)

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
    unsigned long kernel_address;
    char data[128];

    if (cmd == IOCTL_WRITE_MEMORY) {
        if (copy_from_user(&kernel_address, (unsigned long *)arg, sizeof(unsigned long))) {
            pr_err("Failed to copy user data\n");
            return -EFAULT;
        }

        // Vulnerability: Writing data to an arbitrary memory location
        if (copy_from_user(data, "Malicious Data", sizeof(data))) {
            pr_err("Failed to copy user data\n");
            return -EFAULT;
        }

        memcpy((void *)kernel_address, data, sizeof(data));
        pr_info("Data written to 0x%lx: %s\n", kernel_address, data);
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

    driver_class = class_create(THIS_MODULE, "arbitrary_write_driver_class");
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

