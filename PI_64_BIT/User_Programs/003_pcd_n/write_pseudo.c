#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
char buffer[1024];
int device_num ;
int fd;
int bytes_written;
memset(buffer,'\0',1024);

if(argc != 3)
{
printf("Usage: <%s> <pcdev-n,n is device number> <string>\n",argv[0]);
return 0;
}
device_num = atoi(argv[1]);
switch(device_num)
{
case 1:fd = open("/dev/pcdev-1",O_WRONLY);break;
case 2:fd = open("/dev/pcdev-2",O_WRONLY);break;
case 3:fd = open("/dev/pcdev-3",O_WRONLY);break;
case 4:fd = open("/dev/pcdev-4",O_WRONLY);break;
default:printf("Invalid device number\n");return 0;
}

if(fd<0)
{
perror("Error in file opening\n");
close(fd);
return 0;
}

bytes_written = write(fd,argv[2],strlen(argv[2]));
printf("bytes written: %d\n",bytes_written);

close(fd);
return 0;
}
