#include<stdio.h>
#include<malloc.h>

struct char_string {
	char c;
	struct char_string *next;
};

int main(void)
{
	char temp; int i = 1, n = 0;
	struct char_string *head = NULL, *tail,*p;
	//struct char_string* p = head;

	head = (struct char_string *)malloc(sizeof(struct char_string));
	temp = getchar();
	head->c = temp;
	tail = head;
	p = head;

	while ((temp = getchar()) && (temp != '#')) {
		tail->next = (struct char_string *)malloc(sizeof(struct char_string));
		tail = tail->next;
		tail->c = temp;
		i++;
	}
	tail->next = NULL;

	char* save = NULL;
	save = (char*)malloc((i + 1) * sizeof(char));

	//遍历链表
	while (p) {
		*(save + n) = p->c;
		printf("%c", p->c);//&?
		p = p->next;
		n++;
	}
	*(save + n) = '\0';
	printf("\n\n");

	//输出数组
	printf("%s\n", save);
}
