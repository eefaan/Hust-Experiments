#include<stdio.h>

const int length=8*sizeof(int);

void itob(int n,char a[])
{
    int i;
    for(i=0;i<length;i++)
        a[length-i-1]=(n&(1<<i))?'1':'0';
}

int main(void)
{
    int N,n,i;
    char a[length];
    scanf("%d",&N);
    while(N--)
    {
        scanf("%d",&n);
        itob(n,a);
        for(i=0;i<length;i++)
            printf("%c",a[i]);
        printf("\n");
    }
}
