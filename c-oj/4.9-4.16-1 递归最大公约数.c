#include<stdio.h>

int max(int a,int b,int n)
{
    if(a%n==0&&b%n==0)
        return n;
    else
        return max(a,b,n-1);
}

int main(void)
{
    int a,b,n;
    while(scanf("%d %d",&a,&b)!=EOF)
    {
        getchar();
        if(a!=0&&b!=0)
        {
            n=a;
            printf("%d\n",max(a,b,n));
        }

        else
        {
            printf(" ‰»Î¥ÌŒÛ–≈œ¢£°\n");
            return 0;
        }
    }
}
