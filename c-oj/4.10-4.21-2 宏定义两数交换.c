#include<stdio.h>
#define Swap(x,y) x=x+y;y=x-y;x=x-y

int main(void)
{
    int a,b;
    int N;
    scanf("%d",&N);
    while(N--)
    {
        scanf(" %d %d",&a,&b);
        Swap(a,b);
        printf("%d %d\n",a,b);
    }
}
