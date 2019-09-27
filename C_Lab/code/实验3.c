//改错
#include "stdio.h"
long sum_fac();
void main(void)
{
    int k;
    for(k=1;k<6;k++)
         printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
}
long sum_fac(int n)
{
    long s=0;
    int i;
    long fac=1;
    for(i=1;i<=n;i++)
        {
            fac*=i;
            s+=fac;
        }
    return s;
}

//优化算法
#include "stdio.h"
long sum_fac();
long fac();
void main(void)
{
    int k;
    for(k=1;k<6;k++)
         printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
}
long sum_fac(int n)
{
    if (n==1)
        return 1;
    else
        return sum_fac(n-1)+fac(n);
}
long fac(int n)
{
    if(n==1)
        return 1;
    else
        return n*fac(n-1);
}

//改为1/fac
#include "stdio.h"
double sum_fac();
void main(void)
{
    int k;
    for(k=1;k<6;k++)
         printf("k=%d\tthe sum is %f\n",k,sum_fac(k));
}
double sum_fac(int n)
{
    double s=0;
    int i;
    double fac=1;
    for(i=1;i<=n;i++)
        {
            fac*=i;
            s+=(1/fac);
        }
    return s;
}

//跟踪调试
#include <stdio.h>
#include <stdlib.h>
long fabonacci(int n);
void main(void)
{
    int i,k;
    long sum=0,*p=&sum;
    scanf("%d",&k);
    for(i=1;i<=k;i++){
        sum+=fabonacci(i);
        printf("i=%d\tthe sum is %ld\n",i,*p);
    }
}
long fabonacci(int n)
{
    if(n==1 || n==2)
        return 1;
    else
        return fabonacci(n-1)+fabonacci(n-2);
}

/*编程让用户输入两个整数，
计算两个数的最大公约数并且输出之（要求用递归函数实现求最大公约数）。
同时以单步方式执行该程序，观察递归过程。*/
#include<stdio.h>
int max(int a,int b,int n)
{
    if(a%n==0&&b%n==0)
        {return n;}
    else
        {return max(a,b,n-1);}
}

int main(void)
{
    int a,b,n;
    while(scanf(" %d %d",&a,&b)!=EOF)
    {
        if(a!=0)
        {
            n=a;
            printf("%d\n",max(a,b,n));
        }

        else
        {
            return 0;
        }
    }

}


/*编程验证歌德巴赫猜想：一个大于等于4的偶数都是两个素数之和。
编写一个程序证明对于在符号常量BEGIN和END之间的偶数这一猜测成立。
*/
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
    int num_fb,m,n;
    while(scanf(" %d %d",&M,&N)!=EOF)
    {

        if(M!=0)
        {

            for(;M<=N;M++)
            {
                num_fb=M;
                for(m=0;m<num_fb;m++)
                {
                    for(n=0;n<num_fb;n++)
                    {
                        if((p[m]+p[n]==num_fb)&&(M%2==0))
                        {
                            printf("%d=%d+%d\n",num_fb,p[m],p[n]);
                            goto tt;
                        }
                    }
                }
                tt: continue;
            }
            printf("\n");

        }

        else
        {
            return 0;
        }

    }
}
