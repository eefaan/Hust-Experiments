6.2.1
#include "stdio.h"
void main(void)
{
    float a;
    float *p=&a;
    scanf("%f",p);
    printf("%f\n",*p);
}

6.2.2
#include "stdio.h"
#include "string.h"
void main(void)
{
    char *(*p)(char *a,char *b);
    char a[80],b[80],c[160],*result=c;
	int choice,i;
	do{
		printf("\t\t1 copy string.\n");
		printf("\t\t2 connect string.\n");
		printf("\t\t3 exit.\n");
		printf("\t\tinput a number (1-3) please!\n");
		scanf("%d",&choice);
	}while(choice<1 || choice>5);
	switch(choice){
	case 1:
		p=strcpy;
		break;
	case 2:
		p=strcat;
		break;
	case 3:
		goto down;
	}
	getchar();
	printf("input the first string please!\n");
	i=0;
    scanf("%[^\n]s",a);getchar();
	printf("input the second string please!\n");
	i=0;
    scanf("%[^\n]s",b);getchar();
	result=p(a,b);
	printf("the result is %s\n",result);

down:
	;
}

6.3
#include "stdio.h"
char *strcpy(char *, char *);
void main(void)
{
	char a[20], b[60] = "there is a boat on the lake.";
	printf("%s\n", strcpy(a, b));

}
char *strcpy(char *s, char *t)
{
	char *p=s;
	while (*s++ = *t++)
		;
	return (p);
}

