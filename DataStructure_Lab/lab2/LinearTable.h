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
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
typedef struct LNode{  //顺序表（单链表存储结构）的定义
	ElemType data;          //线性表数据
	struct LNode *next;     //指向下一个线性表数据结点的指针
}LNode, *LinkList;

typedef struct MulNode{  //顺序表多表结构的定义
    int list_num;           //操作表序号
    LinkList list_head;     //操作表头指针
    struct MulNode *next;   //指向下一个表头指针结点的指针
}MulNode;

/*-----page 19 on textbook ---------*/
status IntiaList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType *e);
status LocateElem(LinkList L,ElemType e,ElemType *i); //简化过
status PriorElem(LinkList L,ElemType cur,ElemType *pre_e);
status NextElem(LinkList L,ElemType cur,ElemType *next_e);
status ListInsert(LinkList *L,int i,ElemType e);
status ListDelete(LinkList *L,int i,ElemType *e);
status ListTrabverse(LinkList L);  //简化过
status LoadFile(LinkList L,char filename[20]);
status SaveAsFile(LinkList L,char filename[20]);
status MulList(LinkList *L,MulNode *M,int list_num_cur,int list_num);
