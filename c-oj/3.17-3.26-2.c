#include<stdio.h>

int main()
{
	int N,m,n;
	unsigned x;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%u%u%u",&x,&m,&n);
		
		long mask=0xFFFF;
		long mask1=mask<<(m);
		long mask2=mask>>(16-m-n);
		long choosemask=mask1&mask2;//�����߼��� 
		
		//unsigned long pickmask=(mask1<<m)&(mask1>>(15-m-n));
		//unsigned long pickmask=(mask1<<m)^(mask1<<(m+n));
		

		/*char a[10],b[10],c[10],d[10];
		itoa(mask,b,2);
		itoa(finmask,a,2);
		itoa(mask1,c,2);
		itoa(mask2,d,2);
		printf("%s\n",b);
		printf("%s\n",a);
		printf("%s\n",c);
		printf("%s\n",d);//����߼���
		*/
		 
		unsigned p;
		p=choosemask&x;
		//printf("%d\n",p);//���δ���� 
		p=p<<(16-m-n);
		printf("%u\n",p);
	
	}
	return 0;
}  
