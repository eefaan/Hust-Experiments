#include<stdio.h>
#include<limits.h>
int main()
{
	int i,x,p,n;
	scanf("%d%d%d",&x,&p,&n);//输入数据 
	/*
	int x, p, n;
     unsigned int mask = 0;

     scanf("%d %d %d", &x, &p, &n);

     if (p<0 || p>31)   { puts("star point out of range"); return 0; }
     if (n<1)   { puts("positive range number required"); return 0; }
     if (p+n > 32)  { puts("operate index out of range"); return 0; }

     // output original number
     print_bits(x);
     
     // modify mask
     for (; n>0; --n) {
         mask |= 1u << (p+n-1);
     }
     */

	int x2=x;
	int m=sizeof(int) * CHAR_BIT;
	int maskprintbit=1<<(m-1);
	for (i=1;i<=m; ++i)
	{
		putchar(!(x2&maskprintbit)?'0':'1');
		x2<<=1;
		if(!(i%CHAR_BIT)&& i<m) 
		putchar(' ');
	}//输出原x 
	printf("\n");
	
	unsigned long mask=0xFFFFFFFF;
	long mask1=mask<<(p);
	long mask2=mask>>(32-p-n);
	long choosemask=mask1&mask2;//构建逻辑尺 
	
	/* 
	char a[10]; 
	itoa(choosemask,a,2); 
	printf("%s\n",a);//检查逻辑尺 
	*/ 
	
	/*异或*/
	long fin=choosemask^x; 
	
/*	long exmask1= ~choosemask&x;
	long exmask2= choosemask&x;	
	 
	long fin=exmask1|(~exmask2&choosemask);//完成换位 
*/	 
	for (i=1;i<=m; ++i)
	{
		putchar(!(fin&maskprintbit)?'0':'1');
		fin<<=1;
		if(!(i%CHAR_BIT)&& i<m) 
		putchar(' ');
	}//输出换位后x（fin） 
	printf("\n");

	return 0;
 } 
