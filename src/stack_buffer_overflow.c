#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static char kernel_buf[128];

static int device_write(struct file *filp, const char *buf, size_t len, loff_t *off) {
    // No bounds checking on len before copying data
    copy_from_user(kernel_buf, buf, len);

    return len;
}

static struct file_operations fops = {
    .write = device_write,
};

static int __init buffer_overflow_init(void) {
    printk(KERN_INFO "Buffer Overflow Example: Module loaded\n");
    return 0;
}

static void __exit buffer_overflow_exit(void) {
    printk(KERN_INFO "Buffer Overflow Example: Module unloaded\n");
}

module_init(buffer_overflow_init);
module_exit(buffer_overflow_exit);
