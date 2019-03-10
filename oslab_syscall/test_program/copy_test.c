#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	long int amma = syscall(333, "/home/parallels/test.mkv", "/home/parallels/new.mkv");
	printf("Syscall required %ld\n",amma);
	return 0;
}
