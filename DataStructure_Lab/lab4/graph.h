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
typedef char VertexType;//����Ԫ�����Ͷ���

typedef struct ArcNode{  //ͼ�ڽӱ�ʽ�洢�ṹ�Ķ���
    int adjvex;                    //�û���ָ��Ķ����λ��
    struct ArcNode *nextarc;       //ָ����һ������ָ��
    int info;                      //�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode{//ͼ����
    VertexType data;                     //������Ϣ
    ArcNode *firstarc;                   //ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{//ͼͷ���
    AdjList vertices;
    int vexnum,arcnum;                    //ͼ�ĵ�ǰ�������ͻ���
    //int kind;                             //ͼ�������־
}*ALGraph,ALNode;

typedef struct Arc_Relation{//����ϵ
    char tail;                      //��β����
    char head;                      //��ͷ����
    int weight;                     //����Ȩ
    struct Arc_Relation *next;      //ָ����һ����ϵ
}Relation;

typedef struct MulNode{   //��ͼ�ṹ�Ķ���
    int list_num;         //����ͼ���
    ALGraph list_head;     //����ͼͷָ��
    struct MulNode *next; //ָ����һ��ͼͷָ�����ָ��
}MulNode;

void ScanfVR(Relation **VR);//��ȡVR ����(��ʽ)�߹�ϵ
void ScanfVR_insert(Relation **VR,char tail);//����ʱ��ȡVR ����(��ʽ)�߹�ϵ

status CreateGraph(ALGraph *G, char *Vertex, Relation *VR);//����
status DestroyGraph(ALGraph *G);//����

status LocateVex(ALGraph G,int *num,VertexType data);//����ͼG��U(data)��λ����Ϣ
status GetVex(ALGraph G,int num,VertexType *data);//���(λ��Ϊnum��)����ֵ
status PutVex(ALGraph *G,int num,VertexType value);//��v(num)��ֵvalue

VNode* FirstAdjVex(ALGraph G,int num);//��õ�һ�ڽӵ�
VNode* NextAdjVex(ALGraph G,int num,int num_w);//���num���num_v����һ�ڽӵ�

status InsertVex(ALGraph *G,VertexType data,Relation *VR);//���붥��
status DeleteVex(ALGraph *G,int num);//ɾ������
status InsertArc(ALGraph *G,Relation *VR);//���뻡
status DeleteArc(ALGraph *G,int num_v,int num_w);//ɾ����

status DFSTraverse(ALGraph G);//���������������
status BFSTraverse(ALGraph G);//���������������

status LoadFile(ALGraph *G,char *filename);//��ȡ�ļ�
status SaveAsFile(ALGraph G,char *filename);//�洢�ļ�
status MulList(ALGraph *T,MulNode *M,int list_num_cur,int list_num);//��ͼ�л�

