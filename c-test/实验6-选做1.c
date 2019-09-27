#include <stdio.h>
#include <string.h>

#define N 20//xxx.
#define M 10//.xxx

void main( )
{
    char a[1000], b[1000], c[1001] = {0}, flag = 0;
    int i, j, k;
    scanf("%s %s", a, b);

    for(i = M+N, j = M+N, k = M+N+1 ; i >= 0 && j >= 0; i--, j--, k--)
    {
        // '.'
        if(k==N+1)
        {
            c[k]='.';
            k--;
            c[k] = (a[i-1] - '0' + b[j-1] - '0' + flag) % 10 + '0';
            i--;
            j--;
        }
        //main
        else
        {
            c[k] = (a[i] - '0' + b[j] - '0' + flag) % 10 + '0';
            flag = (a[i] - '0' + b[j] - '0' + flag) / 10;
        }
    }

    if(flag != 0)
    {
        c[0] = flag + '0';
    }
    else if(flag == 0)
    {
        for(i=0;c[i+1]!='\0';i++)
            c[i]=c[i+1];
        c[i]='\0';
    }
    printf("%s + %s = %s\n", a, b, c);
}

