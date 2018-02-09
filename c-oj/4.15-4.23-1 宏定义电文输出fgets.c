#include<stdio.h>
#define CHANGE(c) c%2

int main()
{
    int i,N;
    char c[500];
    scanf("%d",&N);
    getchar();

    while(N--)
    {
        fgets(c,500,stdin);

        if(CHANGE(c[0]))
        {
            for(i=0;c[i]!='\0';i++)
            {
                if(c[i]>='a'&&c[i]<='z')
                    c[i]=c[i]-'a'+'A';
                else if(c[i]>='A'&&c[i]<='Z')
                    c[i]=c[i]-'A'+'a';
            }
        }

        printf("%s",c);
    }
    return 0;
}
