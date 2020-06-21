%option yylineno
%{
#include "exp.tab.h"
#include "string.h"
#include "Node.h"

typedef union {
	int type_int;
	char type_id[32];
	PEXP *pexp;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
id   [A-Za-z][A-Za-z0-9]*  
int    [0-9]+
%%
{int}      {yylval.type_int=atoi(yytext); return INT;}
{id}       {strcpy(yylval.type_id,  yytext); 
            return ID;}
[=]        {return ASSIGNOP;}
[+]        {return PLUS;}
[-]        {return MINUS;}
[*]        {return STAR;}
[/]        {return DIV;}
[(]        {return LP;}
[)]        {return RP;}
[;]        {return yytext[0];}   
[ \t]      {;}   
[\n]       {return yytext[0];}   
.          {printf("error in line %d\n",yylineno);}
%%

/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}

