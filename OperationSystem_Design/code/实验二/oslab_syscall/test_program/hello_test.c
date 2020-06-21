#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	long int amma = syscall(332);
	printf("Syscall required %ld\n",amma);
	return 0;
}
