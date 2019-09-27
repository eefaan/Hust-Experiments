#include<stdio.h>
int judge(char c[],int n)
{
    if(n<=1)
        return 1;

    else if(c[0]==c[n-1])
        return judge(c+1,n-2);

    else
        return 0;
}

int main(void)
{
    char c[100];
    int N,l;

    scanf("%d",&N);
    while(N--)
    {
        getchar();
        scanf("%[^\n]s",c);
        l=strlen(c);
        printf("%s\n",judge(c,l)==1?"Yes!":"No!");
    }
}
