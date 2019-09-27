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
typedef char ElemType;//数据元素类型定义

typedef struct BiTNode{  //二叉树链式存储结构的定义
    int key;                            //结点的唯一标识
    ElemType data;                      //结点的数据
    struct BiTNode *lchild, *rchild;    //指向结点左右孩子的指针
}BiTNode, *BiTree;

typedef struct seqqueue{//队列定义
    BiTree data[MAX];   //队列大小
    int front;          //队列头
    int rear;           //队列尾
}seqqueue;

typedef struct MulNode{   //二叉树森林结构的定义
    int list_num;         //操作表序号
    BiTree list_head;     //操作表头指针
    struct MulNode *next; //指向下一个表头指针结点的指针
}MulNode;

status InitBiTree(BiTree *T);//初始化
status DestroyBiTree(BiTree *T);//销毁
status CreatBiTree(BiTree *T,char *definition);//创建char**definition
status ClearBiTree(BiTree *T);//清空
status BiTreeEmpty(BiTree T);//判定是否为空
int BiTreeDepth(BiTree T);//返回树T深度

status Root(BiTree T, int *e, ElemType *elem);//用elem返回T的根
status Value(BiTree T,int e, ElemType *elem);//e是T中某个结点 返回e的值
status Assign(BiTree *T,int e,ElemType elem);//结点赋值

BiTree Parent(BiTree T,int h_e,int e);//获得双亲结点
BiTree LeftChild(BiTree T,int e);//获得左孩子
BiTree RightChild(BiTree T,int e);//获得右孩子
BiTree LeftSibling(BiTree T,int h_e,int e);//获得左兄弟
BiTree RightSibling(BiTree T,int h_e,int e);//获得右兄弟

status InsertChild(BiTree *T,int e,int LR);//插入子树
status DeleteChild(BiTree *T,int e,int LR);//删除子树

status PreOrderTraverse(BiTree T);//前序遍历
status InOrderTraverse(BiTree T);//中序遍历
status PostOrderTraverse(BiTree T);//后序遍历
status LevelOrderTraverse(BiTree T);//层次遍历

status LoadFile(BiTree *T,char *filename);//读取文件
status SaveAsFile(BiTree T,char *filename);//存储文件
status MulList(BiTree *T,MulNode *M,int list_num_cur,int list_num);//多表切换
