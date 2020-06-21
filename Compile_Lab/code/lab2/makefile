result: lex.l parser.y
	bison -d parser.y
	flex lex.l
	gcc -o test lex.yy.c parser.tab.c ast.c ana.c
