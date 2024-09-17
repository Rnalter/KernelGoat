#include<linux/kernel.h>
#include<linux/module.h>
static int __init hello_init(void){
	printk(KERN_INFO "Hello World\n");
	return 0;
}
static void __exit hello_exit(void){
	printk(KERN_INFO "bye");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Archana");
MODULE_DESCRIPTION("A SIMPLE PROGRAM");
