#include<stdio.h>
int minestrlen(char s[])
{
    int i;
    for(i=0 ; s[i] != '\0' ;)
    {
        i++;
    }
    return i;
}

int main()
{
    int N;
    char a[100];
    scanf("%d",&N);
    getchar();
    while(N--)
    {
        scanf("%[^\n]s",a);
        getchar();
        printf("%d\n",minestrlen(a));
    }
    return 0;
}
