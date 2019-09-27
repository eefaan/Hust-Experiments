#include<stdio.h>
int main()
{
	int a,n;
	while(1)
	{
		n=scanf("%d",&a);
		
		if(n!=1)
		{
			break;
		}
		if(a%3!=0)
		{
			printf("0\n");
		}
		else if(a%10==5)
		{
			printf("1\n");
		}
		else if(a%10!=5)
		{
			printf("0\n");
		}
	
	}
	return 0;
 } 
