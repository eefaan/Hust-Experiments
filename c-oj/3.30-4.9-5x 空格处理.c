#include <stdio.h>
int isspace2(char c)
{if((c==' ')||(c=='\t'))
return 1;
else return 0;
}

int main()
{
int state=0;
char ch, first;
while((ch=getchar())!=EOF)
{
    switch(state)
    {
        case 0:
        if(!isspace2(ch)&&ch!='\n')
            {putchar(ch); state=1;}
        break;

        case 1:
        if(isspace2(ch))
            {first=ch;state=2;}
        else if
            (ch=='\n'){putchar('\n');state=0;}
        else
            {putchar(ch);}
        break;

        case 2:
        if(ch=='\n')
            {putchar('\n'); state=0;}
        else if(!isspace2(ch))
            {putchar(first);putchar(ch);state=1;}
        break;
    }
}
return 0;
}
