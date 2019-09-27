#include<stdio.h>
int main (void)
{
	int N;
	char a[100];
	scanf("%d",&N);
	while(N--)
	{
		getchar();
		char c;
		c=getchar();
		if( c >='0'&&c<='9')
		{
			//printf("%x\n",c);
			//sprintf(a,"%ld",c);
			printf("%d\n",c-'0');
		}
		
		else if(c>='a' && c<='f')
		{
			printf("%d\n",c-'a'+10);
		}
		
		else if(c>='A' &&c<='F')
		{
			printf("%d\n",c-'A'+10);
		}
		
		else
		{
			printf("%d\n",c);
		}
	}
 } 
