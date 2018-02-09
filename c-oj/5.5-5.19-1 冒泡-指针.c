#include<stdio.h>
#define N 10

int a[N];

void bubble_sort(int *a);

int main (void)
{
    int i;
    while(scanf("%d",&a[0])!=EOF)
    {
        //input
        for(i=1;i<N;i++)
            scanf("%d",&a[i]);

        //bubble_sort
        bubble_sort(a);

        for(i=0;i<N;i++)
            printf("%d%s",a[i],(i==(N-1))?"\n":"->");
    }
}

void bubble_sort(int *a)
{
    int i,j,temp;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            if(*(a+j)<*(a+j-1)){
                temp=*(a+j); *(a+j)=*(a+j-1); *(a+j-1)=temp;}
}
