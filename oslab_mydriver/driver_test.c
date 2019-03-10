#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 1024
 
int main(void)
{
	int testdev;
	char buf[MAX_SIZE];	//缓冲区
 
	char dir[50] = "/dev/mydevice";    //设备名
 
	testdev = open(dir, O_RDWR | O_NONBLOCK);
 
	if (testdev == -1)
	{
		printf("Device open failed\n");
		return -1;
	}
	//读初始信息
	read(testdev, buf, sizeof(buf));
	printf("%s\n", buf);

	//写信息
	printf("input new message: ");
	gets(buf);
	write(testdev, buf, sizeof(buf));
 
	//读刚才写的信息
	read(testdev, buf, sizeof(buf)); 
	printf("readout new Message: %s\n", buf);
		
	close(testdev);
	return 0;

}
