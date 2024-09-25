#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "vuln_stack_buffer"
#define BUFFER_SIZE 16  // Small buffer size to cause overflow

static int major;
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .write = device_write,
};

// Called when the device is opened
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "vuln_stack_buffer device opened\n");
    return 0;
}

// Called when the device is closed
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "vuln_stack_buffer device closed\n");
    return 0;
}

// Vulnerable write function
static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t len, loff_t *offset) {
    char kernel_buffer[BUFFER_SIZE];  // Small buffer on stack

    printk(KERN_INFO "Writing %zu bytes to the device\n", len);

    // Deliberately vulnerable: No check for buffer overflow
    if (copy_from_user(kernel_buffer, user_buffer, len)) {
        return -EFAULT;  // Error if data copy fails
    }

    printk(KERN_INFO "Data written to the device: %s\n", kernel_buffer);
    return len;  // Return the number of bytes written
}

// Module initialization
static int __init vuln_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Failed to register the device\n");
        return major;
    }
    printk(KERN_INFO "vuln_stack_buffer module loaded with device major number %d\n", major);
    return 0;
}

// Module exit
static void __exit vuln_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "vuln_stack_buffer module unloaded\n");
}

module_init(vuln_init);
module_exit(vuln_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Deliberately vulnerable kernel module (Stack Buffer Overflow)");

