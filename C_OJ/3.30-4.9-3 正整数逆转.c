#include<stdio.h>
int main (void)
{
    int n;
    while(1)
    {
        printf("请输入将被逆转的正整数：");
        scanf("%d",&n);
        if(n>0)
        {
            printf("逆转后的正整数：");
            int i = 10, p=1;
            for(;n/p != 0;i*=10,p*=10)
            {
                int x_one = n%i /p;
                printf ("%d", x_one);
            }
            printf("\n");
        }
        else
        return 0;
    }
}
