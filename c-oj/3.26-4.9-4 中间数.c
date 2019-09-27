#include<stdio.h>
int main()
{
	int A, B, C, X;

tt:while (scanf("%d", &A) != EOF)
{
	scanf("%d %d", &B, &C);

	X = (A >= B ? (A>C ? (B >= C ? B : C) : A) : (B>C ? (A >= C ? A : C) : B));
	if (X == A)
	{
		printf("A:");
	}
	else if (X == B)
	{
		printf("B:");
	}
	else if (X == C)
	{
		printf("C:");
	}
	printf("%d\n", X);

	goto tt;
}
   return 0;
}
