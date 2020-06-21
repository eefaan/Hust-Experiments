%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "Node.h"
extern char *yytext;
extern FILE *yyin;
void display(struct Exp *,int);
%}

%union {
	int type_int;
	char type_id[32];
	struct Exp *pExp;
};

%type  <pExp> line exp       /*ָ��line��exp������ֵ�ǽ��ָ��pExp*/
%token <type_int> INT        /*ָ��INT������ֵ��type_int���дʷ������õ�����ֵ*/
%token <type_id> ID          /*ָ��ID������ֵ��type_id���дʷ������õ��ı�ʶ���ַ���*/

%token LP RP  PLUS MINUS STAR DIV ASSIGNOP       /*��bison�Ը��ļ�����ʱ��������-d�����ɵ�exp.tab.h��
                                      ����Щ���ʽ��б��룬����lex.l�а���exp.tab.hʹ����Щ����������*/

%left PLUS MINUS
%left STAR DIV
%left UMINUS

%%
input:
	 | input line
	 ;
line : '\n'    { ;}
	 | exp '\n' { display($1,0);}                  /*��ʾ�﷨��*/
	 | error '\n' { printf("exp error!\n");}       /*һ�����﷨������������*/
	 ;
exp	 : INT {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=INT_NODE;$$->type_int=$1;}
	 | ID  {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=ID_NODE;strcpy($$->type_id,$1);}
	 | exp PLUS exp {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=PLUS_NODE;  $$->ptr.pExp1=$1;$$->ptr.pExp2=$3;}
	 | exp MINUS exp {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=MINUS_NODE;  $$->ptr.pExp1=$1;$$->ptr.pExp2=$3;}
	 | exp STAR exp {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=STAR_NODE;  $$->ptr.pExp1=$1;$$->ptr.pExp2=$3;}
	 | exp DIV exp {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=DIV_NODE;  $$->ptr.pExp1=$1;$$->ptr.pExp2=$3;}
	 | LP exp RP   {$$=(PEXP)$2;}
     | MINUS exp   %prec UMINUS  {$$=(PEXP)malloc(sizeof(struct Exp)); $$->kind=UMINUS_NODE;  $$->ptr.pExp1=$2;}  
	;
	/*����exp�Ĺ�������嶯�����ɳ����﷨��*/
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return;
	yyparse();
	return 0;
	}
	
yyerror(char *s){
   printf("%s   %s \n",s,yytext);
   
 }

/*
�������У�
flex lex.l
bison -d -v exp.y
gcc -o exp  exp.tab.c lex.yy.c display.c -Lfl -Ly
*/

