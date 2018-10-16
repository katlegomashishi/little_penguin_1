#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("Katlego Mashishi");
MODULE_DESCRIPTION("Hello World Module\n");
MODULE_LICENSE("GPL");

static int __init ft_hello_init(void)
{
		printk(KERN_INFO "Hello World!\n");
		return 0;
}

static void __exit ft_hello_exit(void)
{
		printk(KERN_INFO "Goodbye!\n");
}

module_init(ft_hello_init);
module_exit(ft_hello_exit);
