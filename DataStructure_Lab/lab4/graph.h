#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE -2
#define OVERFLOW -3

#define MAX 1000
#define MAX_VERTEX_NUM 30

typedef int status;
typedef char VertexType;//数据元素类型定义

typedef struct ArcNode{  //图邻接表式存储结构的定义
    int adjvex;                    //该弧所指向的顶点的位置
    struct ArcNode *nextarc;       //指向下一条弧的指针
    int info;                      //该弧相关信息的指针
}ArcNode;

typedef struct VNode{//图顶点
    VertexType data;                     //顶点信息
    ArcNode *firstarc;                   //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{//图头结点
    AdjList vertices;
    int vexnum,arcnum;                    //图的当前顶点数和弧数
    //int kind;                             //图的种类标志
}*ALGraph,ALNode;

typedef struct Arc_Relation{//弧关系
    char tail;                      //弧尾数据
    char head;                      //弧头数据
    int weight;                     //弧的权
    struct Arc_Relation *next;      //指向下一个关系
}Relation;

typedef struct MulNode{   //多图结构的定义
    int list_num;         //操作图序号
    ALGraph list_head;     //操作图头指针
    struct MulNode *next; //指向下一个图头指针结点的指针
}MulNode;

void ScanfVR(Relation **VR);//读取VR 构建(链式)边关系
void ScanfVR_insert(Relation **VR,char tail);//插入时读取VR 构建(链式)边关系

status CreateGraph(ALGraph *G, char *Vertex, Relation *VR);//创建
status DestroyGraph(ALGraph *G);//销毁

status LocateVex(ALGraph G,int *num,VertexType data);//查找图G中U(data)的位置信息
status GetVex(ALGraph G,int num,VertexType *data);//获得(位置为num的)顶点值
status PutVex(ALGraph *G,int num,VertexType value);//对v(num)赋值value

VNode* FirstAdjVex(ALGraph G,int num);//获得第一邻接点
VNode* NextAdjVex(ALGraph G,int num,int num_w);//获得num相对num_v的下一邻接点

status InsertVex(ALGraph *G,VertexType data,Relation *VR);//插入顶点
status DeleteVex(ALGraph *G,int num);//删除顶点
status InsertArc(ALGraph *G,Relation *VR);//插入弧
status DeleteArc(ALGraph *G,int num_v,int num_w);//删除弧

status DFSTraverse(ALGraph G);//深度优先搜索遍历
status BFSTraverse(ALGraph G);//广度优先搜索遍历

status LoadFile(ALGraph *G,char *filename);//读取文件
status SaveAsFile(ALGraph G,char *filename);//存储文件
status MulList(ALGraph *T,MulNode *M,int list_num_cur,int list_num);//多图切换

