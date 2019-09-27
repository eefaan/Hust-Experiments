#include <stdio.h>
#include <math.h> 

int main()
{
int N;
float a,b,c,p,area;

scanf ("%d", &N);
while (N--)
{
	scanf ("%f%f%f",&a,&b,&c);
	
	p= (a+b+c)/2.0;
	area= sqrt(p*(p-a)*(p-b)*(p-c));
	
	printf("area=%.6f\n", area);
}

return 0;
}
