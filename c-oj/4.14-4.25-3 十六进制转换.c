#include<stdio.h>
#define BASE 16
int htoi(char s[])
{
	int j=0,num=0;
	if(s[j]=='0'&&(s[j+1]=='x'||s[j+1]=='X'))
	{
	    j+=2;
	    for(;s[j]!='\0';j++)
            if (s[j]>='0'&&s[j]<='9')
                num=num*BASE + s[j] - '0';
            else if(s[j]>='a'&&s[j]<='z')
                num=num*BASE + s[j] -'a' + 10;
            else if(s[j]>='A'&&s[j]<='Z')
                num=num*BASE + s[j] -'A' + 10;
	    return num;
	}
	else
	    {
	        return -1;
	    }
}

int main(void)
{
    int N;
    char c[100];
    scanf("%d",&N);

    while(N--)
    {
        scanf("%s",c);
        printf("%d\n",htoi(c));
    }
}
