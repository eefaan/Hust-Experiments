#include <stdio.h>
void main(void)
{
/*
//ԭʼ -�Ĵ�
int i,n,s=1;
  printf("Please enter n:");
  scanf("%d",&n);//&n
  for(i=1;i<=n;i++)
    {
		s=s*i;
	}//{}
  printf("%d! = %d",n,s);
*/


/*
//use while
	int i=1,n,s=1;
	printf("please enter n:");
	scanf("%d",&n);
	while(n-i+1)
	{
		s*=i;
		i++;
	}
	printf("%d! = %d",n,s);
*/

/*
//use do-while
	int i=1,n,s=1;
	printf("please enter n:");
	scanf("%d",&n);
	do
	{
		s*=i;
		i++;
	}
	while(n-i+1);
	printf("%d! = %d",n,s);
*/

/*
//n!>=S��С����
  int n,s=1,S;
  printf("Please enter S:");
  scanf("%d",&S);
  for(n=1;;n++)
    {
		s=s*n;
		if(s>=S)
		{
			printf("����n����S����С����Ϊ: n=%d",n);
			return 0;
		}
	}
*/
}
