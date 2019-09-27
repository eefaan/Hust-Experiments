#include<stdio.h>
#include<limits.h>
int main()
{
	int x, n, i=1;
	scanf("%d%d",&x,&n);
	int l=sizeof(int)*CHAR_BIT;
	
	
	if (n/32==0)
	{
	for(;i<=n;i++)
	{
		x=(x>>1|x<<(l-1));
	}
	printf("%d\n",x);
	}

	else
	{
		int y=n%32;
		for (;i<=y;i++)
		{
			x=(x>>1|x<<(l-1));
		}
		printf("%d\n",x);
	}
	return 0;
 } 
