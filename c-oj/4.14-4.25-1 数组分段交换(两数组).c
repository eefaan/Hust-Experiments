#include<stdio.h>
int swap(int u[],int k,int n)
{
	//swap
	int a[60], i, m;
	m = k;
	for (i=0;m<=n;i++,m++)
	{
		a[i] = u[m];
	}
	for (m=0,i--;m<(n-k);i++,m++)
	{
		a[i] = u[m];
	}

	//output
	for (i = 0;i<n;i++)
	{
		if (i != 0)
		{
			printf(" ");
		}
		printf("%d", a[i]);
	}
	printf("\n");
	return 0;
}

int main(void)
{
	int N, n, k, u[60];
	while (scanf("%d %d", &n, &k) != EOF)
	{
		if(n>k&&k>0)
		{
		    //input
            N = n;
            while (n--)
            {
                scanf("%d", &u[N - n - 1]);
            }

            swap(u,k,N);

            getchar();
		}
	}
}
