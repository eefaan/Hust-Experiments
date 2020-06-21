#include "stdio.h"
#include "Node.h"
void display(PEXP T,int indent)
{//对抽象语法树的先根遍历
if (T)
	{
		switch (T->kind) {
		case ID_NODE:	printf("%*cID： %s\n",indent,' ',T->type_id);
				break;
		case INT_NODE:	printf("%*cINT： %d\n",indent,' ',T->type_int);
				break;
		case UMINUS_NODE: printf("%*c%s\n",indent,' ',"UMINUS");
				  display(T->ptr.pExp1,indent+5);
				  break;
		case PLUS_NODE:
		case MINUS_NODE:
		case STAR_NODE:
		case DIV_NODE:
				printf("%*c%s\n",indent,' ',T->kind==PLUS_NODE?"PLUS":(T->kind==MINUS_NODE?"MINUS":(T->kind==STAR_NODE?"STAR":"DIV")));
				display(T->ptr.pExp1,indent+5);
				display(T->ptr.pExp2,indent+5);
		}

	}

}

