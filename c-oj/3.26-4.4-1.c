#include<stdio.h>
#define PI 3.1415926
int main(void)
{
    int N;
    int r,h;
    scanf("%d",&N);
    while(N--)
    {
        scanf("%d%d",&r,&h);
        double S,V;
        S= 2*PI*r*h +2*PI*r*r;
        V= PI*r*r*h;
        printf("%f %f\n",S,V);
    }
}
