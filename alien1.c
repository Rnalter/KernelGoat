#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
static int __init
hello_init(void){
	printk(KERN_INFO "hello kernel\n");
	return 0;
}
static void __exit
hello_exit(void){
	printk(KERN_INFO "goodbye\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ALLEN");
MODULE_DESCRIPTION("A SIMPLE PROGRAM");
