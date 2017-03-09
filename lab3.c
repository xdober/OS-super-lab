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
#ifndef MAXSIZE
#define MAXSIZE 4096
#endif
char data[MAXSIZE]
unsigned int cur_prt, devnum = -1;

int ch_open(struct inode *inode, struct file *filep) {//open
    cur_prt = 0;
    return 0;
}

int ch_release(struct inode *inode, struct file *filep) {//close
    return 0;
}

static ssize_t ch_read(struct file *filep, char __user *buf, size_t size, loff_t *ppos) {
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    if (p>MAXSIZE) {
        return 0;
    }
    if (count>MAXSIZE - p) {
        count = MAXSIZE - p;
    }
    if (copy_to_user(buf, (void *)(data + p), count)) {
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
    if (p>MAXSIZE) {
        return 0;
    }
    if (count>MAXSIZE - p) {
        count = MAXSIZE - p;
    }
    if (copy_from_user(data + p, buf, count)) {
        ret = -EFAULT;
    } else {
        *ppos += count;
        ret = count;
        printk(KERN_INFO "write %d bytes from %d\n", count, p);
    }
    return ret;
}

static const struct file_operations ch_fops = {
    .owner = THIS_MODULE,
    .read = ch_read,
    .write = ch_write,
    .open = ch_open,
    .release = ch_release,
};

static int init_module(void) {
    devnum = register_chrdev(0, "mydev", &ch_fops);
    if (devnum) {
        printk("Succeed!\n");
    } else {
        printk("Faild!\n");
    }
    return devnum;
}

static int cleanup_module(void) {
    if (devnum>=0) {
        unregister_chrdev(devnum, "mydev");
    }
}
