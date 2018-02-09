#include<stdio.h>
#include<string.h>
int main (void)
{
    int n,i,a[12]={0,0,0,0,0,0,0,0,0,0,0,0};
    char c[100];
    scanf("%[^#]s",c);
    n=strlen(c);
    for(i=0;i<n;i++)
    {
        if(c[i]=='0')
            a[0]++;
        else if(c[i]=='1')
            a[1]++;
        else if(c[i]=='2')
            a[2]++;
        else if(c[i]=='3')
            a[3]++;
        else if(c[i]=='4')
            a[4]++;
        else if(c[i]=='5')
            a[5]++;
        else if(c[i]=='6')
            a[6]++;
        else if(c[i]=='7')
            a[7]++;
        else if(c[i]=='8')
            a[8]++;
        else if(c[i]=='9')
            a[9]++;
        else if((c[i]>='a'&&c[i]<='z')||(c[i]>='A'&&c[i]<='Z'))
            a[10]++;
        else a[11]++;
    }
    printf("Number 0: %d\nNumber 1: %d\nNumber 2: %d\nNumber 3: %d\nNumber 4: %d\nNumber 5: %d\n",a[0],a[1],a[2],a[3],a[4],a[5]);
    printf("Number 6: %d\nNumber 7: %d\nNumber 8: %d\nNumber 9: %d\ncharacters: %d\nother: %d\n",a[6],a[7],a[8],a[9],a[10],a[11]);
}
