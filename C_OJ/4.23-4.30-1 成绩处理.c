#include<stdio.h>
#include<string.h>
#define N 100

void select_sort(int a[], int n, char b[N][50])
{
	int i, j, flag, temp=0;
	char temp2[50]={'\0'};
	for (i = 0;i<n;i++)
	{
		flag = i;
		int max = a[i];
		for (j = i + 1;j<n;j++)
			if (a[j] > max)
			{
				max = a[i];
				flag = j;
			}
		if (flag != i)
		{
			temp = a[i];
			a[i] = a[flag];
			a[flag] = temp;

			strcpy(temp2, b[i]);
			strcpy(b[i], b[flag]);
			strcpy(b[flag], temp2);
		}
	}
}

void bubble_sort(char a[N][50],int b[],int n)
{
    int p,i,temp;
    char temp2[50];
    for(p=0;p<n-1;p++)
        for(i=0;i<n-p-1;i++)
            if(b[i]<b[i+1])
    {
        temp=b[i];
        b[i]=b[i+1];
        b[i+1]=temp;

        strcpy(temp2,a[i]);
        strcpy(a[i],a[i+1]);
        strcpy(a[i+1],temp2);
    }
}

int binarysearch(int a[], int n, int key)
{
	int low = 0, mid, high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid]>key) low = mid + 1;
		else if (a[mid]<key) high = mid - 1;
		else return mid;
	}
	return -1;
}

int main(void)
{
	int i, n;
	char a[N][50];
	int b[N];
	scanf("%d", &n);
	getchar();

	//input
	for (i = 0;i<n;i++)
		scanf("%s %d", a[i], &b[i]);

	//sort
	//select_sort(b, n, a);
    bubble_sort(a,b,n);

	//output after sort
	for (i = 0;i<n;i++)
		printf("%-20s %d\n", a[i], b[i]);
	printf("\n");

	//search
	int m, key, save[N];
	scanf("%d", &m);
	getchar();
	for (i = 0;i<m;i++)
	{
		scanf("%d", &key);
		save[i] = binarysearch(b, n, key);
	}

	//output after search
	for (i = 0;i<m;i++)
	{
		if (save[i] != -1)
			printf("%-20s %d\n", a[save[i]], b[save[i]]);
		else
			printf("Not found!\n");
	}
}
