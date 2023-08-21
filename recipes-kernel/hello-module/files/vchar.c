/* 
 *  hello.c - vi du ve linux kernel module
 */

#include <linux/module.h> /* thu vien nay dinh nghia cac macro nhu module_init va module_exit */
#include <linux/device.h>
#include <linux/fs.h>

#define DRIVER_AUTHOR "Pham Anh Duc <phamanhduc11@gmail.com>"
#define DRIVER_DESC   "Character Device Driver"
#define DRIVER_VERSION  "0.1"

struct vchar_st {
    dev_t devNum;
    struct class *devCls;
    struct device *dev;
} vchar_driver;

/* driver init entry*/
static int __init init_vchar_driver(void)
{
    int ret = 0;

    /* cap phat device number */
    vchar_driver.devNum = 0;
    ret = alloc_chrdev_region(&vchar_driver.devNum, 0, 1, "vchar_device");
    if (ret < 0) {
        printk("failed to register device number dynamically\n");
        goto failed_register_devnum;
    }
    printk("allocated device number (%d,%d)\n", MAJOR(vchar_driver.devNum), MINOR(vchar_driver.devNum));

    /* tao device file */
    vchar_driver.devCls = class_create(THIS_MODULE, "class_vchar_dev");
    if(vchar_driver.devCls == NULL) {
        printk("failed to create a device class\n");
        goto failed_create_class;
    }
    vchar_driver.dev = device_create(vchar_driver.devCls, NULL, vchar_driver.devNum, NULL, "vchar_dev");
    if(IS_ERR(vchar_driver.dev)) {
        printk("failed to create a device\n");
        goto failed_create_device;
    }



    printk("Init vchar driver successful!\n");
    return 0;

failed_create_device:
    class_destroy(vchar_driver.devCls);
failed_create_class:
    unregister_chrdev_region(vchar_driver.devNum, 1);
failed_register_devnum:
    return ret;

}

/* driver exit entry*/
static void __exit exit_vchar_driver(void)
{

	/* xoa bo device file */
	device_destroy(vchar_driver.devCls, vchar_driver.devNum);
	class_destroy(vchar_driver.devCls);

	/* giai phong device number */
	unregister_chrdev_region(vchar_driver.devNum, 1);
    printk("Remove vchar driver successfully!\n");
}

module_init(init_vchar_driver);
module_exit(exit_vchar_driver);

MODULE_LICENSE("GPL"); /* giay phep su dung cua module */
MODULE_AUTHOR(DRIVER_AUTHOR); /* tac gia cua module */
MODULE_DESCRIPTION(DRIVER_DESC); /* mo ta chuc nang cua module */
MODULE_VERSION(DRIVER_VERSION); /* mo ta phien ban cuar module */
