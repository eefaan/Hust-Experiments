#include<stdio.h>
#include<math.h>
#define S(a,b,c) (a+b+c)/2
#define AREA(a,b,c) sqrt(S(a,b,c)*(S(a,b,c)-a)*(S(a,b,c)-b)*(S(a,b,c)-c))

int main(void)
{
    double a,b,c;
    while(scanf("%lf%lf%lf",&a,&b,&c)!=EOF)
    {
        if(a>0&&b>0&&c>0)
            printf("%.0lf %lf\n",S(a,b,c),AREA(a,b,c));
        else
            printf("Wrong Input!\n");
    }
}
