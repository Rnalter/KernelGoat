#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>

// Module parameters for user input
static char *payload = NULL;
module_param(payload, charp, 0644);
MODULE_PARM_DESC(payload, "Input payload to trigger heap overflow");

// Global pointer for heap-allocated buffer
static char *heap_buffer = NULL;

// Vulnerable function demonstrating heap overflow
static void trigger_heap_overflow(void)
{
    // Allocate a small buffer on the heap
    // Deliberately smaller than expected input
    heap_buffer = kmalloc(16, GFP_KERNEL);
    
    if (!heap_buffer) {
        printk(KERN_ALERT "Memory allocation failed\n");
        return;
    }

    // VULNERABILITY: No bounds checking with strcpy
    if (payload) {
        printk(KERN_ALERT "Payload length: %lu\n", strlen(payload));
        printk(KERN_ALERT "Attempting to copy payload to heap buffer\n");
        
        // Deliberately overflow the heap-allocated buffer
        strcpy(heap_buffer, payload);
    }
}

// Module initialization function
static int __init heap_overflow_init(void)
{
    printk(KERN_INFO "Heap Overflow Vulnerability Module Loaded\n");

    // Trigger the vulnerable function
    trigger_heap_overflow();

    return 0;
}

// Module cleanup function
static void __exit heap_overflow_exit(void)
{
    // Free the heap buffer if it was allocated
    if (heap_buffer) {
        kfree(heap_buffer);
    }
    
    printk(KERN_INFO "Heap Overflow Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(heap_overflow_init);
module_exit(heap_overflow_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Kernel Module Demonstrating Heap Overflow Vulnerability");