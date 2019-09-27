#include<stdio.h>
int* move();
int main(void)
{
    int u[60],k,i,n;

    //input
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(i=0;i<n;i++)
        scanf("%d",&u[i]);

        move(u,k,n);
        for(i=0;i<n;i++)
        {
            if(i)
                printf(" ");
            printf("%d",u[i]);
        }
        printf("\n");
    }
}

int* move(int a[],int k,int n)
{
    int i,j,first;
    for(i=0;i<k;i++)
    {
        first=a[0];
        for(j=1;j<n;j++)
            a[j-1]=a[j];
        a[n-1]=first;
    }
    return a;
}
