#include<stdio.h>
int main (void)
{
    int N;
    scanf("%d",&N);
    tt:while(N--)
{
    // int p[] 2~100
    int p[100],num;
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
    scanf("%d",&num_fb);
    for(m=0;m<num_fb;m++)
    {
        for(n=0;n<num_fb;n++)
        {
            if((p[m]+p[n]==num_fb))
            {
                printf("%d=%d+%d\n",num_fb,p[m],p[n]);
                goto tt;
            }
        }
    }
    printf("none!\n");

}
}
