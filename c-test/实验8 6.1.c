#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char ch;
	FILE *fp;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL){        /* fp 指向 filename */
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}

	while((ch=fgetc(fp))!=EOF)          /* 从filename中读字符 */
	   putchar(ch);                  /* 向显示器中写字符 */
	fclose(fp);                      /* 关闭filename */
 return 0;
}


#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char ch;
	FILE *fp;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
	if(freopen(argv[1],"r",stdin)==NULL){        /* fp 指向 filename */
		printf("Can't open %s file!\n",argv[1]);
		exit(-1);
	}
    freopen(argv[2],"w",stdout);
	while((ch=getchar())!=EOF)          /* 从filename中读字符 */
	   putchar(ch);                  /* 向显示器中写字符 */
	                      /* 关闭filename */
 return 0;
}


#include<stdio.h>

int main(void)
{
    char a[100];
    FILE *fout;
    fout=fopen("d:\\test.txt","w+");
    while(scanf("%s",a)!=EOF){
        a[0]=a[0]+'A'-'a';
        fprintf(fout,"%s ",a);
    }
    fclose(fout);
}


#include<stdio.h>

int main(void)
{
    char a[100];
    int i=0;
    FILE *fout;
    fout=fopen("d:\\test.txt","w+");
    while(scanf("%[^\n]",a)!=EOF){
        if((a[0]>'a'&&a[0]<'z')||(a[0]>'A'&&a[0]<'Z'))a[0]=a[0]+'A'-'a';
        for(i=1;a[i]!='\0';i++)
            if(a[i-1]==' '&&((a[i]>'a'&&a[i]<'z')||(a[i]>'A'&&a[i]<'Z')))
                a[i]=a[i]+'A'-'a';
        fprintf(fout,"%s",a);
    }
    fclose(fout);
}


#include<stdio.h>

int main(void)
{
    char a[100];
    int i=0;
    FILE *fout;
    fout=fopen("d:\\test.txt","w+");
    while(gets(a)!=NULL){
        if(a[0]>='a'&&a[0]<='z')a[0]=a[0]+'A'-'a';
        for(i=1;a[i]!='\0';i++)
            if(a[i-1]==' '&&a[i]>='a'&&a[i]<='z')
                a[i]=a[i]+'A'-'a';
        fprintf(fout,"%s\n",a);
    }
    fclose(fout);
}
