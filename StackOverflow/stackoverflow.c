#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/slab.h>

// Module parameters for user input
static char *input_buffer = NULL;
module_param(input_buffer, charp, 0644);
MODULE_PARM_DESC(input_buffer, "Input buffer to demonstrate stack overflow");

// Vulnerable function with fixed-size stack buffer
static void vulnerable_copy_function(void)
{
    // VULNERABILITY: Fixed-size stack buffer
    // This buffer is allocated on the kernel stack
    char local_buffer[64];

    // Unsafe copy without length checking
    // This can cause stack overflow if input is longer than buffer
    if (input_buffer) {
        printk(KERN_INFO "Attempting to copy input: %s\n", input_buffer);
        
        // DANGEROUS: Potential stack overflow
        // strcpy does not check buffer bounds
        strcpy(local_buffer, input_buffer);
        
        printk(KERN_INFO "Copied buffer: %s\n", local_buffer);
    }
}

// Module initialization function
static int __init stack_overflow_init(void)
{
    printk(KERN_INFO "Stack Overflow Vulnerability Module Loaded\n");

    // Call the vulnerable function
    vulnerable_copy_function();

    return 0;
}

// Module cleanup function
static void __exit stack_overflow_exit(void)
{
    printk(KERN_INFO "Stack Overflow Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(stack_overflow_init);
module_exit(stack_overflow_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Kernel Module Demonstrating Stack Overflow Vulnerability");
