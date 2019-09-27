#include<stdio.h>
int main(void)
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        unsigned short x,x_hig,x_sho,x_mid,y;
        scanf("%hu",&x);
        unsigned short mask[3] = {0x000F, 0xF000,0x0FF0};
        x_hig = (x&mask[0])<<12;
        x_sho = (x&mask[1])>>12;
        x_mid = x&mask[2];
        //printf("%d,%d\n",mask[0],mask[1]);
        y= x_sho | x_mid |x_hig;
        printf("%hu\n",y);
    }
}
