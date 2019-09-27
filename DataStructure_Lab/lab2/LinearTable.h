/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE -2
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
typedef struct LNode{  //˳���������洢�ṹ���Ķ���
	ElemType data;          //���Ա�����
	struct LNode *next;     //ָ����һ�����Ա����ݽ���ָ��
}LNode, *LinkList;

typedef struct MulNode{  //˳�����ṹ�Ķ���
    int list_num;           //���������
    LinkList list_head;     //������ͷָ��
    struct MulNode *next;   //ָ����һ����ͷָ�����ָ��
}MulNode;

/*-----page 19 on textbook ---------*/
status IntiaList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType *e);
status LocateElem(LinkList L,ElemType e,ElemType *i); //�򻯹�
status PriorElem(LinkList L,ElemType cur,ElemType *pre_e);
status NextElem(LinkList L,ElemType cur,ElemType *next_e);
status ListInsert(LinkList *L,int i,ElemType e);
status ListDelete(LinkList *L,int i,ElemType *e);
status ListTrabverse(LinkList L);  //�򻯹�
status LoadFile(LinkList L,char filename[20]);
status SaveAsFile(LinkList L,char filename[20]);
status MulList(LinkList *L,MulNode *M,int list_num_cur,int list_num);
