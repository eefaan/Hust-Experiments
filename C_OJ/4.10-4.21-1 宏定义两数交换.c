#include<stdio.h>
#define Swap(x,y) x=x+y;y=x-y;x=x-y

int main(void)
{
    int a,b,i;
    for(i=1;scanf("%d %d",&a,&b)!=EOF;i++)
    {
        printf("Case %d:\nBefore Swap:a=%d b=%d\n",i,a,b);
        Swap(a,b);
        printf("After Swap:a=%d b=%d\n\n",a,b);
    }
}
