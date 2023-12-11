/***************************************************************************//**
*  \file       main.c
*
*  \details    I2C Driver to interface with i2c pin expander
*
*  \author     SUMIT ADEP
*
*  \Tested with Linux raspberrypi 3 b+
*
* *******************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define I2C_BUS_AVAILABLE   	(2)	// I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME   	("PE")	// Device and Driver Name
#define PE_SLAVE_ADDR		(0x4E)	// slave address

static struct i2c_adapter *PE_i2c_adapter = NULL;  // I2C Adapter Structure
static struct i2c_client  *PE_i2c_client  = NULL;  // I2C Client Structure

static int I2C_Write(unsigned char *buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit, 
    ** ACK/NACK and Stop condtions will be handled internally.
    */ 
    int ret = i2c_master_send(PE_i2c_client, buf, len);
    
    return ret;
}

static int I2C_Read(unsigned char *out_buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit, 
    ** ACK/NACK and Stop condtions will be handled internally.
    */ 
    int ret = i2c_master_recv(PE_i2c_client, out_buf, len);
    
    return ret;
}

/*
** This function getting called when the slave has been found
** Note : This will be called only once when we load the driver.
*/
static int PE_probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
    
    pr_info("Pin Expander Probed!!!\n");
    
    return 0;
}
/*
** This function getting called when the slave has been removed
** Note : This will be called only once when we unload the driver.
*/
static void PE_remove(struct i2c_client *client)
{   
    pr_info("Pin Expander Removed!!!\n");
    //return 0;
}

/*
** Structure that has slave device id
*/
static const struct i2c_device_id PE_id[] = {
        { SLAVE_DEVICE_NAME, 0 },
        { }
};
MODULE_DEVICE_TABLE(i2c, PE_id);
/*
** I2C driver Structure that has to be added to linux
*/
static struct i2c_driver PE_driver = {
        .driver = {
            .name   = SLAVE_DEVICE_NAME,
            .owner  = THIS_MODULE,
        },
        .probe          = PE_probe,
        .remove         = PE_remove,
        .id_table       = PE_id,
};
/*
** I2C Board Info strucutre
*/
static struct i2c_board_info PE_i2c_board_info = {
        I2C_BOARD_INFO(SLAVE_DEVICE_NAME, PE_SLAVE_ADDR)
    };
    
/*
** Module Init function
*/
static int __init PE_driver_init(void)
{
    int ret = -1;
    PE_i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);
    
    if( PE_i2c_adapter != NULL )
    {
        PE_i2c_client = i2c_new_client_device(PE_i2c_adapter, &PE_i2c_board_info);
        
        if( PE_i2c_client != NULL )
        {
            i2c_add_driver(&PE_driver);
            ret = 0;
        }
        
        i2c_put_adapter(PE_i2c_adapter);
    }
    
    pr_info("Driver Added!!!\n");
    return ret;
}
/*
** Module Exit function
*/
static void __exit PE_driver_exit(void)
{
    i2c_unregister_device(PE_i2c_client);
    i2c_del_driver(&PE_driver);
    pr_info("Driver Removed!!!\n");
}
module_init(PE_driver_init);
module_exit(PE_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUMIT ADEP");
MODULE_DESCRIPTION("Simple I2C Pin Expander Interface)");
MODULE_VERSION("1.34");
