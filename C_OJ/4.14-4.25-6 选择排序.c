#include<stdio.h>
int* choose_sort(int a[],int n)
{
    int i,j,flag,min,mid;
    for(i=0;i<n;i++)
    {
        min=a[i];
        flag=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<min)
            {
                min=a[j];
                flag=j;
            }
        }

        //needn't change
        if(min==a[i])
            continue;

        //need
        mid=a[flag];
        a[flag]=a[i];
        a[i]=mid;
    }
    return a;
}

int main (void)
{
    int N,i,a[100];
    while(scanf("%d",&N)!=EOF)
    {
        if(N)
        {
            //input
            for(i=0;i<N;i++)
                scanf("%d",&a[i]);

            //sort
            choose_sort(a,N);

            //output
            for(i=0;i<N;i++)
                printf("%d%c",a[i],i<N-1?' ':'\n');
        }
        else
            return 0;
    }
}
