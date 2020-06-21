%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
int old_status;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int    type_int;
    float  type_float;
    char   type_char;
	char   type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}

%x COMMENT
%option yylineno

/*  Q:
    数据类型至少包括char类型、int类型和float类型
    基本运算至少包括算术运算、比较运算、逻辑运算、自增自减运算和复合赋值运算
    控制语句至少包括if语句和while语句
    其它选项：数组、结构，for循环等等 */

/* DEFINE */

/* keywords */
id          [_A-Za-z][_A-Za-z0-9]*
int         [+-]?[0-9]+
float       [+-]?([0-9]*\.[0-9]+)|[+-]?([0-9]+\.)
char        [']\\?.?[']
/* STRING      \"(\\.|[^"\n])*$ */
/* COMMENT_TYPE2 */
A [/]
B [*]
C [^*/]

%%
{int}        {printf("<INT, %s>\n",yytext); yylval.type_int=atoi(yytext); return INT;}
{float}      {printf("<FLOAT, %s>\n",yytext); yylval.type_float=atof(yytext); return FLOAT;}
{char}		 {printf("<CHAR, %s>\n",yytext); yylval.type_char=yytext[1]; return CHAR;}
"int"        {printf("<TYPE, %s>\n",yytext); strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {printf("<TYPE, %s>\n",yytext); strcpy(yylval.type_id,  yytext);return TYPE;}
"char"       {printf("<TYPE, %s>\n",yytext); strcpy(yylval.type_id,  yytext);return TYPE;}
"void"		 {printf("<TYPE, %s>\n",yytext); strcpy(yylval.type_id,  yytext);return TYPE;}

"return"     {printf("<RETURN, %s>\n",yytext); return RETURN;}
"if"         {printf("<IF, %s>\n",yytext); return IF;}
"else"       {printf("<ELSE, %s>\n",yytext); return ELSE;}
"while"      {printf("<WHILE, %s>\n",yytext); return WHILE;}
"break"		 {return BREAK;}

{id}       {printf("<ID, %s>\n",yytext); strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{printf("<SEMI, %s>\n",yytext); return SEMI;}
","			{printf("<COMMA, %s>\n",yytext); return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {printf("<RELOP, %s>\n",yytext); strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{printf("<ASSIGNOP, %s>\n",yytext); return ASSIGNOP;}
"+"			{printf("<PLUS, %s>\n",yytext); return PLUS;}
"-"			{printf("<MINUS, %s>\n",yytext); return MINUS;}
"*"			{printf("<STAR, %s>\n",yytext); return STAR;}
"/"			{printf("<DIV, %s>\n",yytext); return DIV;}
"++"		{printf("<SELFADD, %s>\n",yytext); return SELFADD;}
"--"		{printf("<SELFDEC, %s>\n",yytext); return SELFDEC;}
"&&"        {printf("<AND, %s>\n",yytext); return AND;}
"||"        {printf("<OR, %s>\n",yytext); return OR;}
"!"			{printf("<NOT, %s>\n",yytext); return NOT;}
"("			{printf("<LP, %s>\n",yytext); return LP;}
")"			{printf("<RP, %s>\n",yytext); return RP;}
"{"			{printf("<LC, %s>\n",yytext); return LC;}
"}"			{printf("<RC, %s>\n",yytext); return RC;}

"+="		{printf("<ASSIGNPLUS, %s>\n",yytext); return ASSIGNPLUS;}
"-="		{printf("<ASSIGNMINUS, %s>\n",yytext); return ASSIGNMINUS;}
"*="		{printf("<ASSIGNSTAR, %s>\n",yytext); return ASSIGNSTAR;}
"/="		{printf("<ASSIGNDIV, %s>\n",yytext); return ASSIGNDIV;}

[\n]           {}
[ \r\t]        {}

"//".*		{printf("<COMMENT_TYPE1, %s>\n",yytext); }
"/*"{A}*({C}{A}*|{B}|{C})*"*/" {printf("<COMMENT_TYPE2, %s>\n",yytext); }

.			{printf("\nError type A :Mysterious character \"%s\" at Line %d\n",yytext,yylineno);}
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
