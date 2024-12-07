#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>

// Declare module parameters with explicit parameter types
static int input_value = 0;
static char *input_string = NULL;

// Use module_param_string for string parameter to ensure proper handling
module_param(input_value, int, 0644);
MODULE_PARM_DESC(input_value, "An integer input value");

module_param(input_string, charp, 0644);
MODULE_PARM_DESC(input_string, "A string input parameter");

// Intentionally declare a NULL pointer to demonstrate vulnerability
static int *dangerous_ptr = NULL;

// Module initialization function with user input and null pointer dereference
static int __init vulnerable_init(void)
{
    // Print out the user-supplied input values with explicit NULL checks
    printk(KERN_INFO "Vulnerable Kernel Module Loaded\n");
    
    // Safe integer parameter handling
    printk(KERN_INFO "Input Value: %d\n", input_value);
    
    // Safe string parameter handling
    if (input_string) {
        printk(KERN_INFO "Input String: %s\n", input_string);
    } else {
        printk(KERN_WARNING "No string input provided\n");
    }

    // VULNERABILITY: Conditional null pointer dereference
    // This will cause a kernel panic if the conditions are met
    if (input_value > 10) {
        printk(KERN_ALERT "Attempting dangerous pointer dereference\n");
        *dangerous_ptr = input_value;  // Deliberate null pointer dereference
    }

    return 0;
}

// Module cleanup function
static void __exit vulnerable_exit(void)
{
    printk(KERN_INFO "Vulnerable Kernel Module Unloaded\n");
}

// Macro declarations for kernel module
module_init(vulnerable_init);
module_exit(vulnerable_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Security Research");
MODULE_DESCRIPTION("Kernel Module with User Input and Null Pointer Dereference");