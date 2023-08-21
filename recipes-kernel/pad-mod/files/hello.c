
#include <linux/module.h>

int init_module(void)
{
    printk("Hello World from kernel!\n");
    return 0;
}


void cleanup_module(void)
{
    printk("Goodbye from kernel!\n");
}

MODULE_LICENSE("GPL");