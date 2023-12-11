/*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  //copy_to/from_user()
#include <linux/gpio.h>     //GPIO
#include <linux/err.h>
//LED is connected to this GPIO
#define GPIO_21 (21)
#define GPIO_20 (20)
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev g_cdev;
 
static int __init g_driver_init(void);
static void __exit g_driver_exit(void);
 
 
/*************** Driver functions **********************/
static int g_open(struct inode *inode, struct file *file);
static int g_release(struct inode *inode, struct file *file);
static ssize_t g_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t g_write(struct file *filp,const char *buf, size_t len, loff_t * off);
/******************************************************/
 
//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = g_read,
  .write          = g_write,
  .open           = g_open,
  .release        = g_release,
};

/*
** This function will be called when we open the Device file
*/ 
static int g_open(struct inode *inode, struct file *file)
{
  pr_info("Device File Opened...!!!\n");
  return 0;
}

/*
** This function will be called when we close the Device file
*/
static int g_release(struct inode *inode, struct file *file)
{
  pr_info("Device File Closed...!!!\n");
  return 0;
}

/*
** This function will be called when we read the Device file
*/ 
static ssize_t g_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
  char gpio_state = '0';
  
  //reading GPIO value
  gpio_state = gpio_get_value(GPIO_20) + 48;
  
  //write to user
  len = 1;
  if( copy_to_user(buf, &gpio_state, len) > 0) {
    pr_err("ERROR: Not all the bytes have been copied to user\n");
  }
  
  pr_info("Read function : GPIO_20 = %d \n", gpio_state);
  
  return 0;
}

/*
** This function will be called when we write the Device file
*/ 
static ssize_t g_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
  uint8_t rec_buf[10] = {0};
  
  if( copy_from_user( rec_buf, buf, len ) > 0) {
    pr_err("ERROR: Not all the bytes have been copied from user\n");
  }
  
  pr_info("Write Function : GPIO_21 Set = %c\n", rec_buf[0]);
  
  if (rec_buf[0]=='1') {
    //set the GPIO value to HIGH
    gpio_set_value(GPIO_21, 1);
  } else if (rec_buf[0]=='0') {
    //set the GPIO value to LOW
    gpio_set_value(GPIO_21, 0);
  } else {
    pr_err("Unknown command : Please provide either 1 or 0 \n");
  }
  
  return len;
}

/*
** Module Init function
*/ 
static int __init g_driver_init(void)
{
  /*Allocating Major number*/
  if((alloc_chrdev_region(&dev, 0, 1, "g_Dev")) <0){
    pr_err("Cannot allocate major number\n");
    goto r_unreg;
  }
  pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
  /*Creating cdev structure*/
  cdev_init(&g_cdev,&fops);
 
  /*Adding character device to the system*/
  if((cdev_add(&g_cdev,dev,1)) < 0){
    pr_err("Cannot add the device to the system\n");
    goto r_del;
  }
 
  /*Creating struct class*/
  if(IS_ERR(dev_class = class_create(THIS_MODULE,"g_class"))){
    pr_err("Cannot create the struct class\n");
    goto r_class;
  }
 
  /*Creating device*/
  if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"gpio_device_file"))){
    pr_err( "Cannot create the Device \n");
    goto r_device;
  }
  
  //Checking the GPIO is valid or not
  if(gpio_is_valid(GPIO_21) == false && gpio_is_valid(GPIO_20) == false){
    pr_err("GPIO is not valid\n");
    goto r_device;
  }
  
  //Requesting the GPIO
  if(gpio_request(GPIO_21,"GPIO_21") < 0 &&  gpio_request(GPIO_20,"GPIO_20") < 0){
    pr_err("ERROR: GPIO %d and GPIO %d request\n", GPIO_21,GPIO_20);
    goto r_gpio;
  }
  
  //configure the GPIO_21 as output
  gpio_direction_output(GPIO_21, 0);
  //configure the GPIO_20 as input
  gpio_direction_input(GPIO_20);  

  pr_info("Device Driver Insert...Done!!!\n");
  return 0;
 
r_gpio:
  gpio_free(GPIO_21);
  gpio_free(GPIO_20);
r_device:
  device_destroy(dev_class,dev);
r_class:
  class_destroy(dev_class);
r_del:
  cdev_del(&g_cdev);
r_unreg:
  unregister_chrdev_region(dev,1);
  
  return -1;
}

/*
** Module exit function
*/ 
static void __exit g_driver_exit(void)
{
  gpio_free(GPIO_20);
  gpio_free(GPIO_21);
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&g_cdev);
  unregister_chrdev_region(dev, 1);
  pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(g_driver_init);
module_exit(g_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUMIT ADEP");
MODULE_DESCRIPTION("A simple device driver - GPIO Driver");
MODULE_VERSION("1.32");
