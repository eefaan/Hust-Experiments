#include<stdio.h>
int C(int m,int n)//C 右上m 右下n
{
	int i, num, I, M, N;

    if(m==n)
    {
        return 1;
    }

    else
    {
        i=n-m;
        num=i;
        for(;num>1;num--)
        {
            i*=(num-1);
        }
        I=i;//I=(n-m)!

        num=m;
        for(;num>1;num--)
        {
            m*=(num-1);
        }
        M=m;//M=m!

        num=n;
        for(;num>1;num--)
        {
            n*=(num-1);
        }
        N=n;//N=n!

        return N/M/I;
    }
}

int main()
{
	int n;
	int space,i,j,p;
	while(scanf("%d",&n)!=EOF)
    {
        getchar();
        if(n>=1&&n<=12)
        {
            p=n;//记录总行数
            for(;n>0;n--)
            {
                for(space=2*n; space>2; space--)
                {
                    printf(" ");
                }
                printf("1");
                //输出首个数字前空格

                i=p-n;//行
                j=1;
                int q=i+1;
                for(;j<q;j++)
                {
                    printf("%4d",C(j,i));
                }
                printf("\n");
            }
            printf("\n");
        }
        else
        {
            printf("wrong!\n");
        }
    }
    return 0;
}

