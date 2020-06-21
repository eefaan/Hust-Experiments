result:  parser.y lex.l
	bison -d parser.y
	flex lex.l
	gcc -o test parser.tab.c lex.yy.c ast.c
