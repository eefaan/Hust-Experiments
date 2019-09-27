#include<stdio.h>

int hailstone(unsigned n)
{
    unsigned a[10000],i;

    printf("%5u",n);

    for(a[2]=n,i=2;a[i]!=1;i++)
    {

        if(a[i]%2==0)
        {
            a[i+1]=a[i]/2;
        }

        else if(a[i]%2==1)
        {
            a[i+1]=3*a[i]+1;
        }

        printf("%5u",a[i+1]);

        if(i%6==0)
        {
            printf("\n");
        }

    }

    if((i-1)%6!=0)
    {
        printf("\n");
    }

    return 0;
}

int main (void)
{
    int n;

    while(scanf("%u",&n)!=EOF)
    {
        if(n==0)
        {
            return 0;
        }

        else if(n>0)
        {
            hailstone(n);
            printf("\n");
        }
    }
}
