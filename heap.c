#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>  // For kmalloc() and kfree()
#include <linux/uaccess.h> // For copy_from_user()

#define BUF_SIZE 10  // Small buffer size to demonstrate heap overflow

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Divya");
MODULE_DESCRIPTION("A deliberately vulnerable kernel module");
MODULE_VERSION("1.0");

static char *heap_buffer;

/**
 * This function deliberately causes a heap overflow by not checking
 * the length of data copied from user space to kernel space.
 */
static ssize_t vulnerable_function(const char __user *user_input, size_t len) {
    printk(KERN_INFO "vulnerable_function: Allocating %d bytes on the heap\n", BUF_SIZE);

    // Allocate a small buffer on the heap
    heap_buffer = kmalloc(BUF_SIZE, GFP_KERNEL);
    if (!heap_buffer) {
        printk(KERN_ALERT "vulnerable_function: kmalloc failed\n");
        return -ENOMEM;
    }

    // Deliberately copy too much data (more than BUF_SIZE)
    // Vulnerability: No bounds checking, causing heap overflow
    if (copy_from_user(heap_buffer, user_input, len)) {
        printk(KERN_ALERT "vulnerable_function: copy_from_user failed\n");
        kfree(heap_buffer);
        return -EFAULT;
    }

    printk(KERN_INFO "vulnerable_function: Data copied from user, length: %zu\n", len);

    // Free the allocated memory
    kfree(heap_buffer);

    return len;
}

static int __init vulnerable_module_init(void) {
    printk(KERN_INFO "vulnerable_module: Module loaded\n");
    return 0;
}

static void __exit vulnerable_module_exit(void) {
    printk(KERN_INFO "vulnerable_module: Module unloaded\n");
}

module_init(vulnerable_module_init);
module_exit(vulnerable_module_exit);

