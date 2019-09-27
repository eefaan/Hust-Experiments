#include<stdio.h>
int main()
{
	int N,LN;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%u",&LN) ;
		unsigned long mask[4]={0x000000FF,0x0000FF00,0x00FF0000,0xFF000000};
		
		int i=0;
		for(; i<4 ; i++ )
		{long dec =(LN&mask[i])>>(i*8);
		
		char a[100];
		sprintf(a,"%ld",dec);
		
		printf("%s",a);
		if(i!=3)
		printf(".");
		}
		
		printf("\n");
		
	}
	
	return 0;
}
