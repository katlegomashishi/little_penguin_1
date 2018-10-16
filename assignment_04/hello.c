#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/hid.h>

MODULE_AUTHOR("Katlego Mashishi");
MODULE_DESCRIPTION("hello world USB-Keyboard");
MODULE_LICENSE("GPL");

static int pen_probe(struct usb_interface *inetrface,
		const struct usb_device_id *id)
{
		printk(KERN_INFO "USB Keyboard Driver is plugged\n");
		return 0;
}

static void pen_disconnect(struct usb_interface *interface)
{
		printk(KERN_INFO "USB device is disconnected\n");
}

static struct usb_device_id pen_table[] = {
		{USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
				USB_INTERFACE_SUBCLASS_BOOT,
				USB_INTERFACE_PROTOCOL_KEYBOARD)},
		{},
};

MODULE_DEVICE_TABLE(usb, pen_table);

static struct usb_driver my_usb = {
		.name = "USB Keyboard-Driver",
		.id_table = pen_table,
		.probe = pen_probe,
		.disconnect = pen_disconnect,
};

static int __init hello_init(void)
{
		printk(KERN_INFO "Hello World!!\n");
		return usb_register(&my_usb);
}

static void __exit hello_exit(void)
{
		printk(KERN_INFO "Cleaning Up Module\n");
		usb_deregister(&my_usb);
}

module_init(hello_init);
module_exit(hello_exit);
