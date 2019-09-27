#include<stdio.h>
#define n 8
int x[n+1];

int check(int k);

int main(void)
{
    int count=0;
    int i,k=1;

    //flash
    for(i=1;i<=n;i++)
        x[i]=0;

    //main
    while(k)
    {
        x[k]=x[k]+1; //place a queen

        while(x[k]<=n && !check(k))
            x[k]=x[k]+1;//find a right queen

        if(x[k]<=n && k<n)//next queen
            k++;

        else if(x[k]<=n && k==n)//output
        {
            for(i=1;i<=n;i++)
                printf("%d ",x[i]);
            printf("\n\n");
            count++;
        }

        else//go back to last line
        {
            x[k]=0;
            k--;
        }
    }
    printf("sum up : %d\n",count);
}

int check(int k)
{
    int i;
    for(i=1;i<k;i++)
        if(x[k]==x[i] || (k-i)==(x[k]-x[i]) || (k-i)==(x[i]-x[k]))//flase?
            return 0;
    return 1;
}
