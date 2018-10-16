#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kamashis <kat7450mash@gmail.com>");
MODULE_DESCRIPTION("Little penguin / ass05");

#define USERNAME "kamashis"
#define LEN 8


static ssize_t my_read(struct file *f, char *buffer, 
			size_t length, loff_t *offset)
{
	int res;
	char *read_from = USERNAME + *offset;
	size_t read_num = length < (LEN - *offset) ? length : (LEN - *offset);

	if (read_num == 0) {
		res = 0;
		return res;
	}

	res = copy_to_user(buffer, read_from, read_num);
	if (res == read_num) {
		res = -EIO;
	} else {
		*offset = LEN - res;
		res = read_num - res;
	}
	return res;
}

static ssize_t my_write(struct file *f, const char *buf, 
			size_t len, loff_t *offset)
{
	char newbuf[LEN];
	ssize_t res;

	if (len != LEN) {
		res = -EINVAL;
		return res;
	}
	copy_from_user(newbuf, buf, LEN);
	if (strncmp(newbuf, USERNAME, LEN) == 0)
		res = LEN;
	else
		res = -EINVAL;

	return res;
}

static struct file_operations my_fops = {
  .read = my_read,
  .write = my_write,
};

static struct miscdevice my_device = {
	.name = "fortytwo",
	.minor = MISC_DYNAMIC_MINOR,
	.fops = &my_fops,
	.mode = 0666,
};


int __init hello_init(void)
{
	printk(KERN_INFO "Hello world!\n");
	return misc_register(&my_device);
}

void __exit hello_exit(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
	misc_deregister(&my_device);
}

module_init(hello_init);
module_exit(hello_exit);
