#include<stdio.h>
#include<math.h>

float f1(float x)
{
    float y;
    y=x*(x*(3*x-4)-5)+13;
    return y;
}

float f2(float x)
{
    float y;
    y=x*(9*x-8)-5;
    return y;
}

int main (void)
{
    float x0,x1;

    x0=1.0;

    do
    {
        x1=x0;
        x0=x1-f1(x1)/f2(x1);
    }
    while(fabs(x0-x1)>=0.000001);

    printf("%f\n",x0);
}
