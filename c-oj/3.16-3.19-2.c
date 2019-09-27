#include <stdio.h>
int main()
{
	int n,a[10] ;
	int iSum=0;
	int b[100];

	scanf("%d",&n);

	while(n--)
	{
		int iA;
		for(iA=0; iA<10; iA++)
		    scanf("%d",&a[iA]); //数据存入数组a 
		
		int r=0, i;
		for(i=0;i<10;++i)
		    r+=a[i]; //计算数组a的和 
		
		b[iSum]=r; //将和存入数组b 
		iSum+=1;
	}

	int c;
	for(c=0;c<iSum;c++)
	{
		printf("sum=%d.\n",b[c]);
	} //输出数组b 

	return 0;
}
