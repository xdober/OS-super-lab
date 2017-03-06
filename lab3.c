#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <asm/uacess.h>
#include <asm/io.h>
#include <asm/system.h>
#ifndef CHDEV_MAJOR
#define CHDEV_MAJOR 254 //预设设备号
#endif
#ifndef CHDEV_SIZE
#define CHDEV_SIZE 4096
#endif
struct ch_dev { //dev struct
    char *data;
    unsigned long size;
};

static ch_major = CHDEV_MAJOR;
module_param(ch_major, int, S_IRUGO);
struct ch_dev *mydevp;
int ch_open(struct inode *inode, struct file *filep) {//open
    file->private_data = mydevp;
    //printk("======== chdev open");
    return 0;
}

int ch_release(struct inode *inode, struct file *filep) {//close
    //printk("======== chdev close");
    return 0;
}

static ssize_t ch_read(struct file *filep, char __user *buf, size_t size, loff_t *ppos) {
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct ch_dev *dev = filep->private_data;
    if (p>CHDEV_SIZE) {
        return 0;
    }
    if (count>CHDEV_SIZE - p) {
        count = CHDEV_SIZE - p;
    }
    if (copy_to_user(buf, (void *)(dev->data + p), count)) {
        ret = -EFAULT;
    } else {
        *ppos += count;
        ret = count;
        printk(KERN_INFO "read %d bytes from %d\n", count, p);
    }
    return ret;
}
static ssize_t ch_write(struct file *filep, const char __user *buf, size_t size, loff_t *ppos) {
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    struct ch_dev *dev = filep->private_data;
    if (p>CHDEV_SIZE) {
        return 0;
    }
    if (count>CHDEV_SIZE - p) {
        count = CHDEV_SIZE - p;
    }
    if (copy_from_user(dev->data + p, buf, count)) {
        ret = -EFAULT;
    } else {
        *ppos += count;
        ret = count;
        printk(KERN_INFO "written %d bytes from %d\n", count, p);
    }
    return ret;
}

static const struct file_operations ch_fops = {
    .owner = THIS_MODULE,
    .read = ch_read,
    .write = ch_write,
    .open = ch_open,
    .close = ch_release,
};
