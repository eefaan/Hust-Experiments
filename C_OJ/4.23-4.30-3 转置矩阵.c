#include<stdio.h>
#define N 10
int transform(int a[N][N],int b[N][N]);

int main (void)
{
    int a[N][N],b[N][N];
    int m,n;

    //input
    for(m=0;m<3;m++)
        for(n=0;n<4;n++)
            scanf("%d",&a[m][n]);

    //before
    for(m=0;m<3;m++)
        {
            for(n=0;n<4;n++)
                printf("%5d",a[m][n]);
            printf("\n");
        }
        printf("\n");

    //transform
    transform (a,b);

    //after
    for(m=0;m<4;m++)
        {
            for(n=0;n<3;n++)
                printf("%5d",b[m][n]);
            printf("\n");
        }
}

int transform(int a[N][N],int b[N][N])
{
    int m,n;
    for(m=0;m<3;m++)
        for(n=0;n<4;n++)
            b[n][m]=a[m][n];
    return 0;
}
