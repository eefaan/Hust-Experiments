#include<stdio.h>

double useif(double a, double b, char c)
{
	double r;

	if (c == '+') { r = a + b; }
	else if (c == '-') { r = a - b; }
	else if (c == '*') { r = a*b; }
	else if (c == '/') { r = a / b; }
	else { printf("wrong!\n");return 0; }

	return r;
}

double useswitch(double a, double b, char c)
{
	double r;

	switch (c)
	{
	case '+':r = a + b;return r;
	case '-':r = a - b;return r;
	case '*':r = a*b;return r;
	case '/':r = a / b;return r;
	default:return 0;
	}
}

int main(void)
{
	int t;
	double a, b;
	char c[10];
	while ( scanf("%d", &t) != EOF)
	{

		scanf(" %lf %lf %s", &a, &b, c);

		switch (t)
		{
		case 0:printf("After if-else processing,the result is : %.2f\n", useif(a, b, c[0]));break;
		case 2:printf("After if-else processing,the result is : %.2f\n", useif(a, b, c[0]));t--;
		case 1:printf("After switch processing,the result is : %.2f\n", useswitch(a, b, c[0]));break;
		default:break;
		}

		printf("\n");
	}
	return 0;
}
