#include<stdio.h>
int main()
{
	int N, i;
	char f,a[100];//limit a[] long 100
	scanf("%d",&N);
	while (N--)
	{
		fflush(stdin);
		scanf("%c", &f);
		printf("%c", f);
		//getchar();
		scanf(" %[^\n]s", a);
		i = 0;
		for (;a[i] != '\0';)
		{
			if (a[i] == ' ')
			{
				printf(" ");
				while (a[i] == ' ')
				{
					i++;
				}
			}

			else if (a[i] != ' ')
			{
				printf("%c", a[i]);
				i++;
			}
		}
		printf("\n");
	}
	return 0;
}
