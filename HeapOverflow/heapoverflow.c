#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>

// Module parameters for user input
static char *payload = NULL;
static int buffer_size = 16;  // Configurable buffer size
module_param(payload, charp, 0644);
MODULE_PARM_DESC(payload, "Input payload to trigger heap overflow");
module_param(buffer_size, int, 0644);
MODULE_PARM_DESC(buffer_size, "Size of allocated buffer");

// Structures to demonstrate overflow impact
struct vulnerable_struct {
    char buffer[16];    // Main buffer
    int canary;         // Canary to detect overflow
    char next_buffer[16]; // Adjacent buffer to show corruption
};

// Vulnerable function demonstrating heap overflow
static void trigger_heap_overflow(void)
{
    // Allocate a structure on the heap
    struct vulnerable_struct *heap_data = kmalloc(sizeof(struct vulnerable_struct), GFP_KERNEL);
    
    if (!heap_data) {
        printk(KERN_ALERT "Memory allocation failed\n");
        return;
    }

    // Initialize canary with a known value
    heap_data->canary = 0xDEADBEEF;

    // Initialize buffers with known patterns
    memset(heap_data->buffer, 'A', sizeof(heap_data->buffer));
    memset(heap_data->next_buffer, 'B', sizeof(heap_data->next_buffer));

    // Print initial state
    printk(KERN_ALERT "Initial Canary Value: 0x%x\n", heap_data->canary);
    printk(KERN_ALERT "Initial Buffer Content: %.*s\n", 
           (int)sizeof(heap_data->buffer), heap_data->buffer);
    printk(KERN_ALERT "Initial Next Buffer Content: %.*s\n", 
           (int)sizeof(heap_data->next_buffer), heap_data->next_buffer);

    // VULNERABILITY: Overflow with user-supplied payload
    if (payload) {
        printk(KERN_ALERT "Payload Length: %lu\n", strlen(payload));
        printk(KERN_ALERT "Buffer Size: %d\n", buffer_size);

        // Deliberately overflow the buffer
        // Uses memcpy to show exact bytes copied
        memcpy(heap_data->buffer, payload, 
               strlen(payload) > buffer_size ? strlen(payload) : buffer_size);
    }

    // Check for overflow
    printk(KERN_ALERT "After Overflow Canary Value: 0x%x\n", heap_data->canary);
    printk(KERN_ALERT "After Overflow Buffer Content: %.*s\n", 
           (int)sizeof(heap_data->buffer), heap_data->buffer);
    printk(KERN_ALERT "After Overflow Next Buffer Content: %.*s\n", 
           (int)sizeof(heap_data->next_buffer), heap_data->next_buffer);

    // Free the allocated memory
    kfree(heap_data);
}

// Module initialization function
static int __init heap_overflow_init(void)
{
    printk(KERN_INFO "Detailed Heap Overflow Vulnerability Module Loaded\n");

    // Trigger the vulnerable function
    trigger_heap_overflow();

    return 0;
}

// Module cleanup function
static void __exit heap_overflow_exit(void)
{
    printk(KERN_INFO "Heap Overflow Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(heap_overflow_init);
module_exit(heap_overflow_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Detailed Kernel Module Demonstrating Heap Overflow Vulnerability");