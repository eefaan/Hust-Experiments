#include "linux/kernel.h"
#include "linux/module.h"
#include "linux/fs.h"
#include "linux/init.h"
#include "linux/types.h"
#include "linux/errno.h"
#include "linux/uaccess.h"
#include "linux/kdev_t.h"
 
#define MAX_SIZE 1024
 
int my_open(struct inode *inode, struct file *file);
int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f);
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f);
 
char message[MAX_SIZE] = "this is my testing Driver";  //打开设备时会显示的消息
int device_num;//驱动设备号
char* devName = "mydriver";//驱动设备名
 
struct file_operations pStruct = {
	open:my_open, 
	release:my_release, 
	read:my_read, 
	write:my_write, 
};
 
//注册
int init_module()
{
	int ret;
 
	// 向系统登记设备及驱动程序的入口点
	ret = register_chrdev(0, devName, &pStruct);
	if (ret < 0){// 注册失败
		printk("failed to register_chrdev.\n");
		return -1;
	}
	else{// 注册成功
		printk("the Driver has been registered!\n");
		printk("id: %d\n", ret);
		device_num = ret;
		return 0;
	}
}
 
//注销
void cleanup_module()
{
	unregister_chrdev(device_num, devName);
	printk("unregister driver successful.\n");
}
 
 
//打开
int my_open(struct inode *inode, struct file *file)
{
	printk("Open device success!\n");
	try_module_get(THIS_MODULE);
	return 0;
}
 
//关闭
int my_release(struct inode *inode, struct file *file)
{
	printk("Device released!\n");
	module_put(THIS_MODULE);
 
	return 0;
}
 
 
//读设备里的信息
ssize_t my_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
	if(copy_to_user(user,message,sizeof(message)))
	{
		return -2;
	}
	return sizeof(message);
}
 
//向设备里写信息
ssize_t my_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
	if(copy_from_user(message,user,sizeof(message)))
	{
		return -3;
	}
	return sizeof(message);
}
