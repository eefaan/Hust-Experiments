#include<stdio.h>
int main (void)
{
    int M,N;

    // int p[] 2~100
    int p[101],num;
    p[1]=0,p[2]=2;
    for(num=3;num<=100;num++)
    {
        int a=0,i;

        for(i=2;i<num;i++)
        {
            if(num%i ==0)
            {
                a++;
            }
        }

        if(a==0)
        {
            p[num]=num;
        }
        else
        {
            p[num]=0;
        }
    }

    //proof
    int m,n;
    printf("请输入M、N的值：");
    while(scanf("%d %d",&M,&N)!=EOF)
    {
        getchar();
        if(M>=4&&M<=N)
        {
            for(;M<=N;M++)
            {
                for(m=0;m<M;m++)
                {
                    for(n=0;n<M;n++)
                    {
                        if((p[m]+p[n]==M)&&(M%2==0))
                        {
                            printf("%d=%d+%d\n",M,p[m],p[n]);
                            break;
                        }
                    }
                    if((p[m]+p[n]==M)&&(M%2==0))
                    {
                        break;
                    }
                }
            }
            printf("\n");
        }

        else
        {
            printf("请输入正确的M、N!\n\n");
        }
        printf("请输入M、N的值：");
    }
}
