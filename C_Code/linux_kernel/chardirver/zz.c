/*chardev.c*/
#include <linux/kernel.h>
#include <linux/fs.h>                   /*for file-f_op*/
#include <linux/module.h>
#include <asm/uaccess.h>                /*for copy_to_user()*/
#include <linux/cdev.h>                 /*for cdev ,cdev_init,cdev_add....*/


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Helight");

#define DP_MAJOR 250                    /*the major number of the chardev*/
#define DP_MINOR 0                      /*the minor number of the chardev*/
static int char_read(struct file *filp,char __user *buffer,size_t,loff_t *);         /*the read operation of the chardev----read the data from kernel*/
static int char_open(struct inode *,struct file *);                                      /*open the chardev*/
static int char_write(struct file *filp,const char __user *buffer,size_t ,loff_t*); /*write data to kernel*/
static int char_release(struct inode *,struct file *);                                   /*release the chardev*/

static int chropen;                     /*the chardev open or not*/
struct cdev *chardev;                   /*define a char device*/
static int len;

static const struct file_operations char_ops = {
	.read = char_read,
	.write = char_write,
	.open = char_open,
	.release = char_release,
};

static int __init char_init(void)
{
	dev_t dev;
	printk(KERN_ALERT"Initing......\n");
	dev=MKDEV(DP_MAJOR,DP_MINOR);
	chardev = cdev_alloc( );

	if(chardev==NULL){
		return -1;
	}
	if(register_chrdev_region(dev,10,"chardev")){
		printk(KERN_ALERT"Register char dev error\n");
		return -1;
	}
	chropen=0;
	len=0;
	cdev_init(chardev,&char_ops);
	if(cdev_add(chardev,dev,1))
	{
		printk(KERN_ALERT"Add char dev error\n");
	}

	return 0;
}

static int char_open(struct inode *inode,struct file *file)
{
	if(chropen==0)
	  chropen++;
	else{
		printk(KERN_ALERT"Another process open the char device\n");
		return -1;
	}
	try_module_get(THIS_MODULE);
	return 0;
}

static int char_release(struct inode *inode,struct file *file)
{
	chropen--;
	module_put(THIS_MODULE);
	return 0;
}

static int char_read(struct file *filp,char __user *buffer,size_t length,loff_t *offset)
{
	if(length<12) {
		if(!copy_to_user(buffer,"hello world!",length))
		{
			return 0;
		}
	}else
	{
		if(!copy_to_user(buffer,"hello world!",strlen("hello world!")))
		{
			return 0;
		}
	}
	return -1;
}

static int char_write(struct file *filp,const char __user  *buffer,size_t length,loff_t *offset)
{
	return 0;
}

static void __exit module_close(void)
{
	len=0;
	printk(KERN_ALERT"Unloading..........\n");

	unregister_chrdev_region(MKDEV(DP_MAJOR,DP_MINOR),10);
	cdev_del(chardev);
}

module_init(char_init);
module_exit(module_close)
