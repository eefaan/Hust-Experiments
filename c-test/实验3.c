//�Ĵ�
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

//�Ż��㷨
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

//��Ϊ1/fac
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

//���ٵ���
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

/*������û���������������
���������������Լ���������֮��Ҫ���õݹ麯��ʵ�������Լ������
ͬʱ�Ե�����ʽִ�иó��򣬹۲�ݹ���̡�*/
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


/*�����֤��°ͺղ��룺һ�����ڵ���4��ż��������������֮�͡�
��дһ������֤�������ڷ��ų���BEGIN��END֮���ż����һ�²������
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
