#include<stdio.h>
/*
int main(void)
{
    int N,sum=0;
    while(scanf("%d",&N)!=EOF)
    {
        getchar();
        if(N!=0)
        {
            sum+=N;
        }
        else
            break;
    }
    printf("������������ۼӺ�����%d\n",sum);
}
*/
/*
int main (void)
{
    int N,sum=0;
    for(;scanf("%d",&N)!=EOF;)
    {
        getchar();
        if(N!=0)
        {
            sum+=N;
        }
        else
            break;
    }
    printf("������������ۼӺ�����%d\n",sum);
}
*/

int main (void)
{
    int N=1,sum=0;
    do
    {
        if(N!=0)
        {
            sum+=N;
        }
        else
            break;
    }
    while(scanf("%d",&N)!=EOF);
    printf("������������ۼӺ�����%d\n",sum-1);
}
