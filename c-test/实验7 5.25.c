7.2.1
#include<stdio.h>
int main(void)
{

char u[]="UVWXYZ";
char v[]="xyz";
struct T{
	int x;
	char c;
	char *t;
}a[]={{11,'A',u},{100, 'B',v}},*p=a;

//printf("%d",((++p)->x));

//p++;printf("%d",p->c);

//printf("%d",*p++->t);printf("%d",*p->t);

//printf("%d",*(++p)->t);

///printf("%d",*++p->t);

//printf("%c",++*p->t);
}

7.2.2
#include "stdio.h"
#include "stdlib.h"

struct s_list{
    int data; /* ������ */
    struct s_list *next; /* ָ���� */
};

void create_list (struct s_list **headp,int *p);
void create_list_v2(struct s_list **headp,int *p);

void main(void)
{
	struct s_list *head=NULL,*p;
	int s[]={1,2,3,4,5,6,7,8,0}; /* 0Ϊ������� */
	create_list_v2(&head,s); /* ���������� */
	p=head; /*����ָ��pָ����ͷ */
	while(p){
		printf("%d\t",p->data); /* ����������ֵ */
		p=p->next; /*����ָ��pָ����һ��� */
	}
	printf("\n");
}

void create_list(struct s_list **headp,int *p)
{
	struct s_list * loc_head=NULL,*tail;
	if(p[0]==0) /* �൱��*p==0 */
		;
	else { /* loc_headָ��̬����ĵ�һ����� */
		loc_head=(struct s_list *)malloc(sizeof(struct s_list));
		loc_head->data=*p++; /* ��������ֵ */
		tail=loc_head; /* tailָ���һ����� */
		while(*p){ /* tail��ָ����ָ����ָ��̬�����Ľ�� */
			tail->next=(struct s_list *)malloc(sizeof(struct s_list));
			tail=tail->next; /* tailָ���´����Ľ�� */
			tail->data=*p++; /* ���´����Ľ���������ֵ */
		}
		tail->next=NULL; /* ��ָ����NULLֵ */
	}
	*headp=loc_head; /* ʹͷָ��headpָ���´��������� */
}

void create_list_v2(struct s_list **headp,int *p)
{
    struct s_list * loc_head=NULL, *tail;

    if (p[0]==0);
    else {
        loc_head=(struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data=*p++;
        loc_head->next=NULL;

        while(*p){
            tail=(struct s_list *)malloc(sizeof(struct s_list));
            tail->next=loc_head;
            tail->data=*p++;
            loc_head=tail;
        }
    }
    *headp=loc_head;
}



������
#include<stdio.h>
#include<malloc.h>

struct s_list{
	int data;
	struct s_list *next;
};

void foo(struct s_list *a,struct s_list *b)
{
    struct s_list *p, *q, *k, *t, *s;
    for (p = a, q = b ; p && q ; p = p->next, q = q->next);

    k = p?p:q;
    t = p?a:b;
    s = p?b:a;

    for (; t; printf("%d ", t->data), t = t->next);
    printf("\n");
    for (; k; printf("  "), k = k->next);
    for (; s; printf("%d ", s->data), s = s->next);
}

void create_list(struct s_list **headp,int *p)
{	struct s_list * loc_head=NULL,*tail;
	if(p[0]==0) ;
	else {
		loc_head=(struct s_list *)malloc(sizeof(struct s_list));
		loc_head->data=*p++;
		tail=loc_head;
		while(*p){
			tail->next=(struct s_list *)malloc(sizeof(struct s_list));
			tail=tail->next;
			tail->data=*p++;
		}
		tail->next=NULL;
	}
	*headp=loc_head;
}

int main(void)
{	struct s_list *m=NULL,*n=NULL;
	int s[]={1,2,3,4,5,6,7,8,0},t[]={8,9,0};
		create_list(&m,s);
		create_list(&n,t);
		foo(m,n);
}

