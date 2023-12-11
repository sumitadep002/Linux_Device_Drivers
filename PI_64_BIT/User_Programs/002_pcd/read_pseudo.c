#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
char buffer[512];
memset(buffer,'\0',512);
if(argc != 2)
{
printf("Usage: ./objectfile <Number_of_bytes_to_read>\n");
return 0;
}
int fd = open("/dev/pcd",O_RDONLY,0666);
if(fd<0)
{
perror("Error in file opening\n");
close(fd);
return 0;
}
int bytes_read  = 0 ;
bytes_read = read(fd,buffer,atoi(argv[1]));
printf("Read data: %s\n",buffer);
printf("bytes read: %d\n",bytes_read);

close(fd);
return 0;
}
