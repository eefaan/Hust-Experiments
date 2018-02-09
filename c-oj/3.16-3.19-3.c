#include <stdio.h>
#include <math.h> 
#define S(a,b,c) ((a+b+c)/2.0)
#define AREA(s,a,b,c)  sqrt(s*(s-a)*(s-b)*(s-c))

int main()
{
int N;
double a,b,c,s,area;

scanf ("%d", &N);

while (N--)
{
	scanf("%lf%lf%lf",&a,&b,&c);
	
	s= S(a,b,c);
	area= AREA(s,a,b,c);
	
	printf("area=%.6f\n",area);
}

return 0;
}
