#include<stdio.h>
int main(void)
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        unsigned short x, mask[2]={0x00FF, 0xFF00};
        scanf("%hu",&x);
        int i = 1;
        for( ;i>=0;i--)
        {
            unsigned short x_half = (x&mask[i]) >>(i*8);
            printf("%c",(char)x_half);
            if(i!=0)
            printf(",");
        }
        printf("\n");
    }
}
