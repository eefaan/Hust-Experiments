#include<stdio.h>

int n;

void swap(int *a);

int main(void)
{
    int N,i,a[100];
    scanf("%d",&N);

    while(N--)
    {
        //input
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);

        //swap
        swap(a);

        //out put
        for(i=0;i<n;i++)
            printf("%d%c",a[i],i==(n-1)?'\n':' ');
    }
}

void swap(int *a)
{
    int i,temp;
    for(i=0;i<n-i;i++)
    {
        temp=*(a+i);
        *(a+i)=*(a+n-1 -i);
        *(a+n-1 -i)=temp;
    }
}
