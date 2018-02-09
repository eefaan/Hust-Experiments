#include<stdio.h>
#define CHANGE(c) c%2

int main(void)
{
    int i,N;
    char c[100];

    scanf("%d",&N);
    while(N--)
    {
        getchar();
        scanf("%[^\n]",c);

        if(CHANGE(c[0])==0)
            printf("%s\n",c);

        else
        {
            for(i=0;c[i]!='\0';i++)
            {
                if(c[i]>='a'&&c[i]<='z')
                {
                    c[i]=c[i]-32;
                }
                else if(c[i]>='A'&&c[i]<='Z')
                {
                    c[i]=c[i]+32;
                }
                printf("%c",c[i]);
            }
            printf("\n");
        }
    }
}
