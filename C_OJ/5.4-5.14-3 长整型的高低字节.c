#include<stdio.h>
#define N 100
#define length 32

char s[N][N];

void itoh(long a[],int n);

int main (void)
{
    long a[N];
    int n,i,j;
    scanf("%d",&n);

    //input
    for(i=0;i<n;i++)
        scanf("%ld",a+i);

    //main
    itoh(a,n);

    //output
    for(i=0;i<n;i++)
        for(j=0;j<15;j++)
            printf("%c%c",*(*(s+i)+j),j==14?'\n':' ');
}

void itoh(long a[],int n)
{
    int i,j,temp=0;

    for(j=0;j<n;j++)
    {
        long mask=0XF0000000;

        for(i=0;i<8;i++)
        {
            temp=(  ( (mask>> (i*4) ) & *(a+j) ) >> (28-i*4)  )& 0xF ;
            if(temp>=0&&temp<10)
                *(*(s+j)+i)='0'+temp;
            else if(temp>9)
                *(*(s+j)+i)='A'+temp-10;
        }
        *(*(s+j)+i)='\0';
    }
}
