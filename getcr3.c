#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/string.h>
#include <linux/wait.h>		/* wait_queue_head_t */
#include <linux/interrupt.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>

//#define	DEBUG

#ifndef	DRV_NAME
#define	DRV_NAME	"getcr3"
#endif
#ifndef	DRV_IDX
#define	DRV_IDX		(0)
#endif
#define	DRV_VERSION	"0.0.0"
#define	getcr3_DRIVER_NAME	DRV_NAME " getcr3 driver " DRV_VERSION

#if LINUX_VERSION_CODE > KERNEL_VERSION(3,8,0)
#define	__devinit
#define	__devexit
#define	__devexit_p
#endif


static int getcr3_open(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);

	return 0;
}

static ssize_t getcr3_read(struct file *filp, char __user *buf,
			   size_t count, loff_t *ppos)
{
#ifdef __x86_64__
	u64 cr0, cr2, cr3;
	__asm__ __volatile__ (
		"mov %%cr0, %%rax\n\t"
		"mov %%eax, %0\n\t"
		"mov %%cr2, %%rax\n\t"
		"mov %%eax, %1\n\t"
		"mov %%cr3, %%rax\n\t"
		"mov %%eax, %2\n\t"
	: "=m" (cr0), "=m" (cr2), "=m" (cr3)
	: /* no input */
	: "%rax"
	);
	if ( copy_to_user( buf, (unsigned char *)&cr3, sizeof(u64) ) ) {
		printk( KERN_INFO "copy_to_user failed\n" );
		return -EFAULT;
	}
	return sizeof(u64);
#elif defined(__i386__)
	u32 cr0, cr2, cr3;
	__asm__ __volatile__ (
		"mov %%cr0, %%eax\n\t"
		"mov %%eax, %0\n\t"
		"mov %%cr2, %%eax\n\t"
		"mov %%eax, %1\n\t"
		"mov %%cr3, %%eax\n\t"
		"mov %%eax, %2\n\t"
	: "=m" (cr0), "=m" (cr2), "=m" (cr3)
	: /* no input */
	: "%eax"
	);
	if ( copy_to_user( buf, (unsigned char *)&cr3, sizeof(u32) ) ) {
		printk( KERN_INFO "copy_to_user failed\n" );
		return -EFAULT;
	}
	return sizeof(u32);
#endif
}


static struct file_operations getcr3_fops = {
	.owner		= THIS_MODULE,
	.read		= getcr3_read,
	.open		= getcr3_open,
};

static struct miscdevice getcr3_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DRV_NAME,
	.fops = &getcr3_fops,
};

static int __devinit getcr3_init(void)
{
	int ret;

#ifdef MODULE
	pr_info(getcr3_DRIVER_NAME "\n");
#endif
	printk("%s\n", __func__);

	/* register character device */
	ret = misc_register(&getcr3_dev);
	if (ret) {
		printk("fail to misc_register (MISC_DYNAMIC_MINOR)\n");
		goto error;
	}

	return 0;

error:

	return ret;
}

static void __exit getcr3_cleanup(void)
{
	misc_deregister(&getcr3_dev);

	printk("%s\n", __func__);
}

MODULE_LICENSE("GPL");
module_init(getcr3_init);
module_exit(getcr3_cleanup);
