#include<stdio.h>
int main(void)
{
    int y, m, d, n, i;
    while(scanf("%d",&y)!=EOFz)
    {
        scanf(" %d %d",&m,&d);

        //初始化month
        int mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        if(y%4==0 && y%100!=0 ||y%400==0)
        {
            mon[2]=29;
        }

        for(n=0,i=1;i<m;i++)
        {
            n+=mon[i];
        }

        printf("该日期是这一年中的第%d天\n",n+d);
    }
}
