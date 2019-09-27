#include <stdio.h>
#include <stdlib.h>

int main()
{
  int t=0,N,a[10] ;
  scanf("%d",&N);
    for(;t<N;t++)
    {
      int i=0,sum=0;
      for(;i<10;i++)
         {
            scanf("%d", &a[i]);
            sum+=a[i];
         }
      printf("sum=%d\n",sum);
    }
    return 0;
}

