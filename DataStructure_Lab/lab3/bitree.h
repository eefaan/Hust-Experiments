#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE -2
#define OVERFLOW -2

#define MAX 1000

typedef int status;
typedef char ElemType;//����Ԫ�����Ͷ���

typedef struct BiTNode{  //��������ʽ�洢�ṹ�Ķ���
    int key;                            //����Ψһ��ʶ
    ElemType data;                      //��������
    struct BiTNode *lchild, *rchild;    //ָ�������Һ��ӵ�ָ��
}BiTNode, *BiTree;

typedef struct seqqueue{//���ж���
    BiTree data[MAX];   //���д�С
    int front;          //����ͷ
    int rear;           //����β
}seqqueue;

typedef struct MulNode{   //������ɭ�ֽṹ�Ķ���
    int list_num;         //���������
    BiTree list_head;     //������ͷָ��
    struct MulNode *next; //ָ����һ����ͷָ�����ָ��
}MulNode;

status InitBiTree(BiTree *T);//��ʼ��
status DestroyBiTree(BiTree *T);//����
status CreatBiTree(BiTree *T,char *definition);//����char**definition
status ClearBiTree(BiTree *T);//���
status BiTreeEmpty(BiTree T);//�ж��Ƿ�Ϊ��
int BiTreeDepth(BiTree T);//������T���

status Root(BiTree T, int *e, ElemType *elem);//��elem����T�ĸ�
status Value(BiTree T,int e, ElemType *elem);//e��T��ĳ����� ����e��ֵ
status Assign(BiTree *T,int e,ElemType elem);//��㸳ֵ

BiTree Parent(BiTree T,int h_e,int e);//���˫�׽��
BiTree LeftChild(BiTree T,int e);//�������
BiTree RightChild(BiTree T,int e);//����Һ���
BiTree LeftSibling(BiTree T,int h_e,int e);//������ֵ�
BiTree RightSibling(BiTree T,int h_e,int e);//������ֵ�

status InsertChild(BiTree *T,int e,int LR);//��������
status DeleteChild(BiTree *T,int e,int LR);//ɾ������

status PreOrderTraverse(BiTree T);//ǰ�����
status InOrderTraverse(BiTree T);//�������
status PostOrderTraverse(BiTree T);//�������
status LevelOrderTraverse(BiTree T);//��α���

status LoadFile(BiTree *T,char *filename);//��ȡ�ļ�
status SaveAsFile(BiTree T,char *filename);//�洢�ļ�
status MulList(BiTree *T,MulNode *M,int list_num_cur,int list_num);//����л�
