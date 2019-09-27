#include<stdio.h>
#include<string.h>
#define N 100

void strnins(char s[], char t[], int n);

int main (void)
{
    char a[2][N];
    int n;

    printf("Please input string s:\n");
    scanf("%[^\n]",a[0]);
    getchar();

    printf("Please input string t:\n");
    scanf("%[^\n]",a[1]);
    getchar();

    printf("Please input the number to insert t to s:\n");
    scanf("%d",&n);

    strnins(a[0],a[1],n);
    printf("After insert:\n%s\n",a[0]);
}

void strnins(char s[], char t[], int n)
{
    char temp[N];
    int i,tempn=n;

    //save
    for(i=0;tempn<=strlen(s);)
        temp[i++]=s[tempn++];

    //insert
    for(i=0;t[i]!='\0';)
        s[n++]=t[i++];

    //copy
    for(i=0;temp[i]!='\0';)
        s[n++]=temp[i++];

    s[n]='\0';

}
