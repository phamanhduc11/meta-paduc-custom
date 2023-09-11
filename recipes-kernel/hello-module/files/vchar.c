/* 
 *  hello.c - vi du ve linux kernel module
 */

#include <linux/module.h> /* thu vien nay dinh nghia cac macro nhu module_init va module_exit */
#include <linux/fs.h> /* thu vien nay dinh nghia cac ham cap phat/giai phong device number */
#include <linux/device.h> /* thu vien nay chua cac ham phuc vu viec tao device file */
#include <linux/slab.h> /* thu vien nay chua cac ham kmalloc va kfree */
#include <linux/cdev.h> /* thu vien nay chua cac ham lam viec voi cdev */
#include <linux/uaccess.h> /* thu vien nay chua cac ham trao doi du lieu giua user va kernel */

#define DRIVER_AUTHOR "Pham Anh Duc <phamanhduc11@gmail.com>"
#define DRIVER_DESC   "Character Device Driver"
#define DRIVER_VERSION  "0.1"

#define DRIVER_BUFFER_SIZE 32

struct vchar_st {
    dev_t devNum;
    struct class *devCls;
    struct device *dev;
    struct cdev *cdev;
    uint8_t *buffer;
} vchar_driver;

/* cac ham entry points */
static int vchar_driver_open(struct inode *inode, struct file *filp)
{
	printk("Handle opened event \n");
    snprintf(vchar_driver.buffer, DRIVER_BUFFER_SIZE, "%s", "Hello after open file");
	return 0;
}

static int vchar_driver_release(struct inode *inode, struct file *filp)
{
	printk("Handle closed event\n");
	return 0;
}

static ssize_t vchar_driver_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	char *kernel_buf = NULL;
	int num_bytes = 0;

	printk("Handle read event start from %lld, %zu bytes\n", *off, len);

	kernel_buf = kzalloc(len, GFP_KERNEL);
	if(kernel_buf == NULL)
		return 0;

	num_bytes = vchar_hw_read_data(vchar_drv.vchar_hw, *off, len, kernel_buf);
	printk("read %d bytes from HW\n", num_bytes);

	if(num_bytes < 0)
		return -EFAULT;
	if(copy_to_user(user_buf, kernel_buf, num_bytes))
		return -EFAULT;

	*off += num_bytes;
	return num_bytes;
}

static ssize_t vchar_driver_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	char *kernel_buf = NULL;
	int num_bytes = 0;
	printk("Handle write event start from %lld, %zu bytes\n", *off, len);

	kernel_buf = kzalloc(len, GFP_KERNEL);
	if(copy_from_user(kernel_buf, user_buf, len))
		return -EFAULT;

	num_bytes = vchar_hw_write_data(vchar_drv.vchar_hw, *off, len, kernel_buf);
	printk("writes %d bytes to HW\n", num_bytes);

	if(num_bytes < 0)
		return -EFAULT;

	*off += num_bytes;
	return num_bytes;
}

static struct file_operations dev_fops  = {
	.owner   = THIS_MODULE,
	.open    = vchar_driver_open,
	.release = vchar_driver_release,
	.read    = vchar_driver_read,
	.write   = vchar_driver_write,
};

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

	/* cap phat bo nho cho cac cau truc du lieu cua driver va khoi tao */
	vchar_driver.buffer= kzalloc(DRIVER_BUFFER_SIZE, GFP_KERNEL);
	if(!vchar_driver.buffer) {
		printk("failed to allocate data structure of the driver\n");
		ret = -ENOMEM;
		goto failed_allocate_structure;
	}
	/* khoi tao thiet bi vat ly */
    // this example doesn't need this

	/* dang ky cac entry point voi kernel */
	vchar_driver.cdev = cdev_alloc();
	if(vchar_driver.cdev == NULL) {
		printk("failed to allocate cdev structure\n");
		goto failed_allocate_cdev;
	}
	cdev_init(vchar_driver.cdev, &dev_fops);
	ret = cdev_add(vchar_driver.cdev, vchar_driver.devNum, 1);
	if(ret < 0) {
		printk("failed to add a char device to the system\n");
		goto failed_allocate_cdev;
	}

	/* dang ky ham xu ly ngat */


    printk("Init vchar driver successful!\n");
    return 0;

failed_allocate_cdev:
    kfree(vchar_driver.buffer);
failed_allocate_structure:
	device_destroy(vchar_driver.devCls, vchar_driver.devNum);
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
	/* huy dang ky xu ly ngat */

	/* huy dang ky entry point voi kernel */
    cdev_del(vchar_driver.cdev);
	/* giai phong thiet bi vat ly */
    // no need cause didn't create anything

	/* giai phong bo nho da cap phat cau truc du lieu cua driver */
    kfree(vchar_driver.buffer);

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
