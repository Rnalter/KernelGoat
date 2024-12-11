#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/limits.h>

// Module parameters for user input
static int input_a = 0;
static int input_b = 0;
module_param(input_a, int, 0644);
MODULE_PARM_DESC(input_a, "First input value");
module_param(input_b, int, 0644);
MODULE_PARM_DESC(input_b, "Second input value");

// Vulnerable function demonstrating integer overflow
static void trigger_integer_overflow(void)
{
    // Integer multiplication with potential overflow
    printk(KERN_INFO "Input A: %d, Input B: %d\n", input_a, input_b);

    // VULNERABILITY: Multiplication without overflow checking
    // Potential to cause integer overflow
    int result = input_a * input_b;

    // Demonstration of different overflow scenarios
    printk(KERN_ALERT "Multiplication Result: %d\n", result);

    // Another vulnerable calculation
    unsigned int unsigned_result;
    if (__builtin_umul_overflow(input_a, input_b, &unsigned_result)) {
        printk(KERN_ALERT "Unsigned Multiplication Overflow Detected\n");
    } else {
        printk(KERN_INFO "Unsigned Multiplication Result: %u\n", unsigned_result);
    }

    // Allocation size overflow
    size_t allocation_size = input_a * input_b;
    char *buffer = kmalloc(allocation_size, GFP_KERNEL);
    
    if (buffer) {
        printk(KERN_ALERT "Memory Allocated: %zu bytes\n", allocation_size);
        kfree(buffer);
    } else {
        printk(KERN_ALERT "Memory Allocation Failed\n");
    }
}

// Module initialization function
static int __init integer_overflow_init(void)
{
    printk(KERN_INFO "Integer Overflow Vulnerability Module Loaded\n");

    // Trigger the vulnerable function
    trigger_integer_overflow();

    return 0;
}

// Module cleanup function
static void __exit integer_overflow_exit(void)
{
    printk(KERN_INFO "Integer Overflow Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(integer_overflow_init);
module_exit(integer_overflow_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Kernel Module Demonstrating Integer Overflow Vulnerability");