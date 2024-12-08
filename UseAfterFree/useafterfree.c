#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>

// Module parameters for user input
static char *payload = NULL;
module_param(payload, charp, 0644);
MODULE_PARM_DESC(payload, "Input payload to trigger use-after-free");

// Global pointer for heap-allocated buffer
static char *sensitive_data = NULL;

// Vulnerable function demonstrating use-after-free
static void trigger_use_after_free(void)
{
    // Allocate memory
    sensitive_data = kmalloc(64, GFP_KERNEL);
    if (!sensitive_data) {
        printk(KERN_ALERT "Memory allocation failed\n");
        return;
    }

    // Initially copy some data
    if (payload) {
        strncpy(sensitive_data, payload, 63);
        sensitive_data[63] = '\0';
        printk(KERN_INFO "Initial data: %s\n", sensitive_data);
    }

    // FREE THE MEMORY
    kfree(sensitive_data);
    printk(KERN_ALERT "Memory freed\n");

    // VULNERABILITY: USE AFTER FREE
    // Attempting to use the pointer after it has been freed
    if (payload) {
        printk(KERN_ALERT "Attempting to use freed pointer\n");
        // This is dangerous - accessing already freed memory
        strcpy(sensitive_data, payload);
        printk(KERN_ALERT "Data after free: %s\n", sensitive_data);
    }
}

// Module initialization function
static int __init use_after_free_init(void)
{
    printk(KERN_INFO "Use-After-Free Vulnerability Module Loaded\n");

    // Trigger the vulnerable function
    trigger_use_after_free();

    return 0;
}

// Module cleanup function
static void __exit use_after_free_exit(void)
{
    // Note: We intentionally do NOT free sensitive_data here
    // as it has already been freed in the trigger function
    printk(KERN_INFO "Use-After-Free Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(use_after_free_init);
module_exit(use_after_free_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Kernel Module Demonstrating Use-After-Free Vulnerability");