#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>

int main()
{
int fd = open("/dev/gpio_device_file",O_WRONLY,0666);
if(fd<0)
{
perror("Error in file opening\n");
close(fd);
return 0;
}
while(1)
{
write(fd,"1",1);
printf("GPIO_21 OUTPUT: HIGH\n");
sleep(1);
write(fd,"0",1);
printf("GPIO_21 OUTPUT: LOW\n");
sleep(1);
}
close(fd);
return 0;
}
