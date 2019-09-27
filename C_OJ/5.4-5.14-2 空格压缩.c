#include<stdio.h>
#define N 100

void zip(char s[N][N]);

int n;
char *p[N];

int main(void)
{
	char s[N][N];
	int i;


	while (scanf("%d", &n) != EOF)
	{
		if (n == 0) return 0;
		else
		{
			//input
			for (i = 0;i<n;i++)
			{
				getchar();
				s[i][0]='\0';
				scanf("%[^\n]", s[i]);
			}

			//main
			zip(s);

			//output
			for (i = 0;i<n;i++)
				if (s[i][0] != '\0') printf("%s%c", s[i], '\n');
            printf("\n");
		}
	}
}

void zip(char s[N][N])
{
	int i, j, t;

	for (t = 0;t<n;t++)
	{
	    i=0;j=0;
		p[t] = s[t];
		while (*(p[t] + j) != '\0')
		{
			if (*(p[t] + j) == ' ')
			{
				if (*(p[t] + j - 1) == ' ')
					j++;
				else
					*(p[t] + i++) = *(p[t] + j++);
			}
			else
				*(p[t] + i++) = *(p[t] + j++);
		}
		*(p[t]+i)='\0';
	}
}
