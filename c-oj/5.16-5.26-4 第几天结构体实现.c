#include<stdio.h>

struct DAY{
    int year;
    int month;
    int day;
};

int judge(int a)
{
    if(((a%4==0)&&(a%100!=0))||a%400==0) return 1;
    else return 0;
}

int leap_year(int a,int b)
{
    int s[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
    int i,sum=0;
    for(i=0;i<a;i++) sum+=s[i];
    sum+=b;
    return sum;
}

int normal_year(int a,int b)
{
    int s[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i,sum=0;
    for(i=0;i<a;i++) sum+=s[i];
    sum+=b;
    return sum;
}

int main(void)
{
    int N;
    struct DAY input_day;

    scanf("%d",&N);
    while(N--)
    {
        scanf("%d %d %d",&input_day.year,&input_day.month,&input_day.day);

        if(judge(input_day.year)) printf("%d\n",leap_year(input_day.month,input_day.day));
        else printf("%d\n",normal_year(input_day.month,input_day.day));
    }
}
