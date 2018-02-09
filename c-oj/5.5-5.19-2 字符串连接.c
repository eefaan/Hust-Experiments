#include<stdio.h>
#define N 100

int n;

void strlink(char a[N][N]);

int main(void)
{
	int i;
	char s[N][N];

	while (scanf("%d", &n) != EOF)
	{

		if (n==0) return 0;

		else
		{
			//input
			for (i = 0;i<n;i++) {
                getchar();  scanf("%[^\n]", s[i]);
			}

			//link
			strlink(s);

			//output
			printf("%s\n", s[0]);
		}
	}
}

void strlink(char a[N][N])
{
	int i;
	char *p0 = a[0] ,*p1;

	while (*p0 != '\0') p0++;

	for (i = 1;i<n;i++)
	{
		p1 = a[i];
		for (;*p1 != '\0';)
			*p0++ = *p1++;
	}

	*p0 = '\0';
}
