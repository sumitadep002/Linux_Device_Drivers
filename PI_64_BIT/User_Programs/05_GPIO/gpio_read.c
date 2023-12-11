#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()
{
char buffer;
int fd = open("/dev/gpio_device_file",O_RDONLY,0600);
if(fd<0)
{
perror("Error in file opening\n");
close(fd);
return 0;
}
while(1)
{
read(fd,&buffer,1);
if(buffer=='1')
printf("GPIO_20 INPUT: HIGH\n");
else
printf("GPIO_20 INPUT: LOW\n");
sleep(1);
}
close(fd);
return 0;
}
