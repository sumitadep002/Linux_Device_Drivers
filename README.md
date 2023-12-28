# Linux Device Driver Repository

This repository contains Linux device driver-related work, including various examples and user programs. If you have any questions or concerns, please contact [adepsumit123@gmail.com](mailto:adepsumit123@gmail.com).

## Directories

### 1. PI_64_BIT

#### Drivers

1. **01_Module_Init**
   - Simple example to print a string whenever a kernel module is loaded/unloaded from the system.

2. **02_Pseudo_Char_Driver**
   - A pseudo driver to overwrite system calls like open, read, write, and copy, etc.

3. **03_Pseudo_Char_Driver_Multiple**
   - Pseudo driver for multiple pseudo devices to overwrite system calls like open, read, write, and copy, etc.

4. **04_Pcd_Platform_Drivers**
   - Understanding platform devices.

5. **05_GPIO**
   - Kernel module to use GPIO.

6. **06_I2C_Pin_Expander**
   - Kernel module to use GPIO.

#### User_Programs

1. **002_pcd**
   - User program to use a single pseudo device driver.

2. **003_pcd_n**
   - User program to use multiple pseudo devices.

3. **05_GPIO**
   - User program to use GPIO kernel module to interface with GPIO.

4. **06_I2C**
   - User program to use I2C kernel module to interface with I2C.
      - **Arduino_Slave:** Arduino code to use Arduino UNO to interface with I2C as a slave.

### Study_Material

- **Linux_Kernel_Module_01.txt**
   - A small explanation of a simple kernel module.

- **manuals**
   - Contains manuals and technical documents about the target device.

- **Pseudo_Character_Driver**
   - Explanation of the pseudo driver.

## Contact Information

For any inquiries, please contact [adepsumit123@gmail.com](mailto:adepsumit123@gmail.com).

