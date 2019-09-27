#include<stdio.h>

int num_strlen(unsigned long n)
{
	unsigned long long i = 1, length = 0;

	if (n == 0)
	{
		return 1;
	}
	else
	{
		for (; n / i != 0;)
		{
			i *= 10;
			length++;
		}

		return length;
	}
}

int num_k(unsigned long n, int k)
{
	int i;
	unsigned long long p;

	if (k>num_strlen(n))
	{
		return -1;
	}

	else
	{
		for (i = 1, p = 1 ;i<k;i++)
		{
			p *= 10;
		}
		p = n % (p * 10) / p;

		return p;
	}


}

int main(void)
{
	unsigned long n;
	int k;

	while (scanf(" %lu %d", &n, &k) != EOF)
	{
		printf("%d\n", num_k(n, k));
	}
}
