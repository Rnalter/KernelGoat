#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// Init Function

static int __init null_dereference_init(void) {
    int *ptr = NULL;
    int value;

    // Null pointer dereference: Attempting to read memory at NULL address
    value = *ptr;

    printk(KERN_INFO "Value: %d\n", value); // This line might not be reached due to a crash

    return 0;
}

// Exit Function
static void __exit null_dereference_exit(void) {
    printk(KERN_INFO "Null Pointer Dereference Example: Module unloaded\n");
}

module_init(null_dereference_init);
module_exit(null_dereference_exit);
