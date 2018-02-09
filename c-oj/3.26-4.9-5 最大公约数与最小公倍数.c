#include<stdio.h>
int main (void)
{
    int m,n,i,minemax,minemin;
    while(scanf("%d%d",&m,&n)==2)
    {
        if(m!=0&&n!=0)
        {
            for(i=1;i<=m&&i<=n;i++)
            {
                if(m%i==0&&n%i==0)
                {
                    minemax=i;
                }
            }
            minemin=m*n/minemax;

            printf("%d %d\n",minemax,minemin);
        }
        else
        {
            return 0;
        }
    }
}
