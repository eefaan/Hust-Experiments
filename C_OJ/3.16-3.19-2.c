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
		    scanf("%d",&a[iA]); //���ݴ�������a 
		
		int r=0, i;
		for(i=0;i<10;++i)
		    r+=a[i]; //��������a�ĺ� 
		
		b[iSum]=r; //���ʹ�������b 
		iSum+=1;
	}

	int c;
	for(c=0;c<iSum;c++)
	{
		printf("sum=%d.\n",b[c]);
	} //�������b 

	return 0;
}
