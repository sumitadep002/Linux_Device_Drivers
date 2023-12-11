#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define ADDR (0x27)


int main(int argc,char *argv[])
{
char temp;
char data[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
char read_data;

int fd = open("/dev/i2c-1",O_RDWR);
perror("open");

ioctl(fd,I2C_SLAVE,ADDR);
perror("ioctl");

for(int i=0;i<=7;i++)
{
write(fd,&data[i],1);
perror("write");

read(fd,&read_data,1);
perror("read");
printf("%x\n",read_data);

read(0,&temp,1);
}
close(fd);
return 0;
}
