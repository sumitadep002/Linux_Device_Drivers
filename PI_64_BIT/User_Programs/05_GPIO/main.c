#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
if(argc != 2)
{
printf("Usage: %s 1 or 2\n",argv[0]);
return 0;
}
int fd = open("/dev/gpio_device_file",O_WRONLY,0666);
if(fd<0)
{
perror("Error in file opening\n");
close(fd);
return 0;
}
int bytes_written  = 0 ;
bytes_written = write(fd,argv[1],1);
printf("bytes written : %d\n",bytes_written);

close(fd);
return 0;
}
