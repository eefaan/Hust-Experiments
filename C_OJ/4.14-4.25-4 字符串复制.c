#include<stdio.h>
char* mycpy(char s[],char t[],int n)//t(n)¡ús
{
    int i;
    for(i=0;i<n;i++)
        s[i]=t[i];
    return s;
}

int main (void)
{
    int N,n,i;
    char c[100],str[100];
    scanf("%d",&N);

    while(N--)
    {
        getchar();
        scanf("%[^\n]s",c);
        scanf("%d",&n);

        mycpy(str,c,n);

        for(i=0;i<n;i++)
            printf("%c",str[i]);
        printf("\n");
    }
}
