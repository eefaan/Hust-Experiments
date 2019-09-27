#include"graph.h"
void main(void){

    MulNode *MulList_head=NULL;//����ͷ,��data��洢������
    MulNode *MulList_temp=NULL;//���ڱ��������������б���
    //��ʼ�����ṹ
    MulList_head = (MulNode*)malloc(sizeof(MulNode));
    MulList_head->list_num= 1;//��ͷdata��洢������
    MulList_head->list_head=NULL;
    MulList_head->next=(MulNode*)malloc(sizeof(MulNode));//�½���1
    MulList_head->next->list_num=1;//����Ϊ1
    MulList_head->next->list_head=NULL;
    MulList_head->next->next=NULL;

    int list_num=1;//ͼ��ţ����֣�
    int list_num_cur=0;//��¼��ǰͼ���
    int flag;//�������м�¼��������ֵ

    ALGraph G=NULL;//��ǰͼͷ���

    char Vertex[MAX];//���㼯��
    Vertex[0]='\0';//��ʼ��
    Relation *VR=NULL;//VR�߹�ϵ��ͷ���

    int i,j,k,flag_c;//�����������ڼ���vertex���㼯�Ƿ��ظ�
    int num;//����v��λ��num
    int num_w;//����w��λ��num
    char filename[MAX];//�ļ�����
    VertexType data;//��������
    VertexType value;//���ڸ�ֵ�Ķ���ֵ
    VNode *temp=NULL;//���ز��ҵ��Ķ���

    int op=1;

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Graph On Adjacency List \n");
        printf("      ��ǰ������ͼ���Ϊ%d\n",list_num);
        printf("-------------------------------------------------\n");
        printf("    	  1.  CreateGraph         2.  DestroyGraph\n");
        printf("    	  3.  LocateVex           4.  GetVex\n");
        printf("    	  5.  PutVex              6.  FirstAdjVex\n");
        printf("    	  7.  NextAdjVex\n");
        printf("-------------------------------------------------\n");
        printf("    	  8.  InsertVex           9.  DeleteVex\n");
        printf("    	  10. InsertArc           11. DeleteArc\n");
        printf("-------------------------------------------------\n");
        printf("    	  12. DFSTraverse         13. BFSTraverse\n");
        printf("-------------------------------------------------\n");
        printf("    	  14. LoadFile            15. SaveAsFile\n");
        printf("    	  16. MulGraph\n");
        printf("-------------------------------------------------\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~16]:");
        fflush(stdin);
        scanf("%d",&op);

    switch(op){
        case 1:
            //����ͼ
            if(G) {
                printf("      ͼ�Ѵ���������ʧ�ܣ�\n");
                getchar();
            }
            else{
                //���붥�㼯
                printf("      �����붥�㼯(���Ȳ�����%d���ַ���)\n      ",MAX_VERTEX_NUM);
                scanf("%s",Vertex);
                getchar();
                fflush(stdin);

                //Vertex�����м�鶥�����
                k=strlen(Vertex);//�������
                if(k>MAX_VERTEX_NUM){//�����붥�����
                    printf("      ���붥�㳬�����ޣ����������˵�\n");
                    Vertex[0]='\0';
                    getchar();
                    break;
                }

                if(Vertex[0]=='\0'){//���㼯��ʽ����
                    printf("      ���㼯�����ʽ���󣡽��������˵�\n");
                    getchar();
                    break;
                }

                //Vertex�����м���ظ�����
                flag_c=0;//����Ƿ��鵽�ظ�����
                for(i=0;i<k-1;i++){//˫��ѭ������ظ�����
                    for(j=i+1;j<k;j++){
                        if(Vertex[i]==Vertex[j]){//��鵽�ظ�����
                            flag_c=1;
                            break;
                        }
                    }
                    if(flag_c) break;
                }

                if(flag_c){//�����㼯�����ظ�����
                    printf("      ���㼯�к����ظ����㣬�������󣡽��������˵�\n");
                    Vertex[0]='\0';
                }
                else{//������ȡ�߹�ϵ
                    ScanfVR(&VR);
                    if(CreateGraph(&G,Vertex,VR->next)==OK) printf("\n      ͼ������ɣ�\n");
                    else printf("      �洢�ռ䲻�㣬����ʧ�ܣ�\n");
                }
            }
            getchar();
            break;
        case 2:
            //����
            if(!G) printf("      ͼδ������\n");
            else{
                if(DestroyGraph(&G)==OK) printf("      ͼ���ٳɹ���\n");
            }
            getchar();getchar();
            break;
        case 3:
            //����data��λ����Ϣ
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      ����������data����Ϊ�����ظö����λ��\n\n");
                getchar();
                printf("      data��");
                scanf("%c",&data);
                if(LocateVex(G,&num,data)==OK) printf("      ͼ�ж���%c���ڽӱ��е�λ��Ϊ%d",data,num);
                else printf("      ͼ��δ�ҵ�dataΪ%c�Ķ��㣡\n",data);
            }
            getchar();getchar();
            break;
        case 4:
            //���Ҷ�Ӧλ�õ�data
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      ������λ��num����Ϊ�����ظö�������\n\n");
                printf("      num��");
                scanf("%d",&num);
                if(GetVex(G,num,&data)==OK) printf("      ͼ��λ��Ϊ%d�Ķ��������Ϊ%c\n",num,data);
                else printf("      ������λ��Ϊ%d�Ķ��㣡\n",num);
            }
            getchar();getchar();
            break;
        case 5:
            //��Ӧλ�ö��㸳ֵΪvalue
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      ������λ��num������value����Ϊ�ö��㸳ֵ\n\n");
                printf("      num��");
                scanf("%d",&num);
                getchar();
                printf("      value��");
                scanf("%c",&value);
                if(PutVex(&G,num,value)==OK) printf("      ͼ��λ��Ϊ%d�Ķ����ֵ���ĳɹ�\n",num);
                else printf("      ������λ��Ϊ%d�Ľ�㣡\n",num);
            }
            getchar();getchar();
            break;

        case 6:
            //���num����ĵ�һ�ڽӵ�
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      �����붥��v��λ��num����Ϊ�����ظö���ĵ�һ�ڽӵ�\n\n");
                printf("      (����v)num��");
                scanf("%d",&num);
                temp=FirstAdjVex(G,num);
                if(temp!=NULL) printf("      ͼ��λ��Ϊ%d�Ķ���ĵ�һ�ڽӵ��λ��numΪ%d������dataΪ%c\n",num,G->vertices[num].firstarc->adjvex,temp->data);
                else printf("      ����ʧ�ܣ�\n");
            }
            temp=NULL;//�ÿ��ݴ���
            getchar();getchar();
            break;
        case 7:
            //���num���������num_w����һ�ڽӵ�
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      �����붥��v��w��λ��num����Ϊ������v������u�������һ�ڽӵ�\n\n");
                printf("      (����v)num��");
                scanf("%d",&num);
                printf("      (����w)num��");
                scanf("%d",&num_w);
                temp=NextAdjVex(G,num,num_w);
                if(temp!=NULL) printf("      ͼ��λ��Ϊ%d�Ķ���v���w����һ�ڽӵ������dataΪ%c\n",num,temp->data);
                else printf("      ����ʧ�ܣ�\n");
            }
            temp=NULL;//�ÿ��ݴ���
            getchar();getchar();
            break;
        case 8:
            //���붥��
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      �����붥�����ݣ���Ϊ�����ڽӱ��в���ö���\n\n");
                printf("      data��");
                getchar();
                scanf("%c",&data);
                getchar();
                ScanfVR_insert(&VR,data);//��ȡ�߹�ϵ

                if(InsertVex(&G,data,VR->next)==OK) printf("      ���붥��ɹ���\n");
                else printf("      ���붥��ʧ�ܣ�\n");
            }
            getchar();
            break;
        case 9:
            //ɾ������
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      �����붥������data����Ϊ��ɾ���ö���\n\n");
                printf("      data��");
                getchar();
                scanf("%c",&data);
                if(LocateVex(G,&num,data)==OK){
                    if(DeleteVex(&G,num)==OK) printf("      ɾ������ɹ���\n");
                    else printf("      ɾ������ʧ�ܣ�\n");
                }
                else{
                    printf("      ���ڽӱ���δ��ѯ��ֵΪ%c�Ķ��㣡\n",data);
                }
            }
            getchar();getchar();
            break;
        case 10:
            //���뻡
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                getchar();
                ScanfVR(&VR);
                if(InsertArc(&G,VR->next)==OK) printf("      ������ɣ�\n");
                else printf("      ����ʧ�ܣ�\n");
            }
            getchar();
            break;
        case 11:
            //ɾ����
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      �����붥��v��w��λ��num����Ϊ��ɾ���������ǵĻ�\n\n");
                printf("      (����v)num��");
                scanf("%d",&num);
                getchar();
                printf("      (����w)num��");
                scanf("%d",&num_w);
                if(DeleteArc(&G,num,num_w)==OK) printf("      ɾ�����ɹ���\n");
                else printf("      ɾ����ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 12:
            //DFS
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      ͼ��������ȱ��������\n");
                printf("--------------------------------------------\n");
                DFSTraverse(G);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 13:
            //BFS
            if(!G) printf("      ͼδ������\n");//ͼ������
            else{
                printf("      ͼ�Ĺ�����ȱ��������\n");
                printf("--------------------------------------------\n");
                BFSTraverse(G);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 14:
            //��ȡ�ļ�
            if(!G){
                printf("      ͼδ������\n");//ͼ������
                getchar();
            }
            else{
                printf("      �����ļ��ж�ȡ���ݲ����ǵ�ǰͼ.\n      ������Ҫ��ȡ���ļ���: ");getchar();
                gets(filename);
                if(LoadFile(&G,filename)==OK) printf("      �ļ���ȡ�ɹ���\n");
                else printf("      �ļ���ȡʧ�ܣ�\n");
            }
            getchar();
            break;
        case 15:
            //�洢�ļ�
            if(!G){
                printf("      ͼδ������\n");//ͼ������
                getchar();
            }
            else{
                printf("      ��ͼ�����ݱ���(д)Ϊ�ļ�\n      ������Ҫд����ļ���: ");getchar();
                gets(filename);
                if(SaveAsFile(G,filename)==OK) printf("      �ļ�д��ɹ���\n");
            }
            getchar();
            break;
        case 16:
            list_num_cur=list_num;//��¼��ǰͼ���Դ洢����
            printf("      ������Ҫ�л�����ͼ��ţ�");
            scanf("%d",&list_num);

            flag=MulList(&G,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      �л��ɹ�����ǰ����ͼΪͼ%d\n",list_num);
            else if(flag==ERROR) printf("      ͼ%d�����ڣ���Ϊ���½�ͼ%d���л�(δ��ʼ��)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//��ͼ����ʧ��
                printf("      �ռ䲻�㣬ͼ����ʧ�ܣ�\n");
                list_num=list_num_cur;//��ǰͼ�����������ǰ
            }

            //�������ͼ���
            printf("\n------------------- all list --------------------\n");
            printf("      ��ǰ����%d��ͼ�ɹ�����\n      �����Ϊ(������ʱ������)��\n      ",MulList_head->list_num);
            for(MulList_temp=MulList_head;MulList_temp->next!=NULL;MulList_temp=MulList_temp->next){//������б���
                printf("%d ",MulList_temp->next->list_num);
            }
            printf("\n---------------------- end ----------------------\n");

            getchar();getchar();
            break;
        case 0:
            break;

        }//end of switch

    }//end of while

    printf("\n      ��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

/**
 * �������ƣ�ScanfVR
 * �������ܣ����ڶ�ȡVR�߹�ϵ�����Ӻ���
 **/
void ScanfVR(Relation **VR)
{
    //��ȡ�߹�ϵVR
    char tail,head;
    int weight=-1;
    *VR=(Relation*)malloc(sizeof(Relation));
    (*VR)->next=NULL;
    Relation *temp=*VR;//���ڱ���
    Relation *insert=NULL;//��������

    printf("\n    Tips����֧�ֹ������߻�����Ȩ��\n");
    printf("          �������룺a b 6\n");
    printf("    �����������ӵĶ���ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ");
    while(scanf("%c %c %d",&tail,&head,&weight)!=EOF){
        if(tail=='\n'||tail==' '||head=='\n'||head==' '||weight<=0||tail==head){//����ȡ��ʽ����
            printf("      �����ʽ���󣬽�������������\n");
            printf("    �����������ӵĽ��ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ");
            fflush(stdin);
            continue;
        }
        getchar();
        //�½�㸳ֵ
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //����
        temp->next=insert;
        temp=temp->next;
        printf("    �����������ӵĽ��ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ");

        fflush(stdin);//���������
        weight=-1;//����Ȩ
    }
    printf("\n");
}

/**
 * �������ƣ�ScanfVR_insert
 * �������ܣ����ڶ�ȡVR�߹�ϵ�����Ӻ���
 **/
void ScanfVR_insert(Relation **VR,char tail)
{
    //��ȡ�߹�ϵVR
    char head;
    int weight=-1;
    *VR=(Relation*)malloc(sizeof(Relation));
    (*VR)->next=NULL;
    Relation *temp=*VR;//���ڱ���
    Relation *insert=NULL;//��������

    printf("\n    Tips����֧�ֹ������߻�����Ȩ��\n");
    printf("          �������룺b 6\n");
    printf("    ���������붥��%c���ӵĶ���ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ",tail);
    while(scanf("%c %d",&head,&weight)!=EOF){
        if(head=='\n'||head==' '||weight<=0||tail==head){//����ȡ��ʽ����
            printf("      �����ʽ���󣬽�������������\n");
            printf("    �����������ӵĽ��ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ");
            fflush(stdin);
            continue;
        }
        getchar();
        //�½�㸳ֵ
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //����
        temp->next=insert;
        temp=temp->next;
        printf("    �����������ӵĽ��ֵ����ߵ�Ȩ��,�����ļ�βֹͣ��ȡ\n      ");

        fflush(stdin);//���������
        weight=-1;//����Ȩ
    }
    printf("\n");
}

/**
 * �������ƣ�Link
 * �������ܣ����ڸ���λ�������ڽӱ�����������
 * ����ֵ���ɹ����ӷ���OK�����򷵻�ERROR
 **/
status Link(ALGraph *G, ArcNode *insert_arc, int tail_vex, int head_vex)
{
	//���ڽӱ����û�insert_arc����(tail_vex,head_vex)
	ArcNode *temp = NULL;//���ڱ����ڽӻ�

	if (!(*G)->vertices[tail_vex].firstarc) {//����β���ڽӻ�
		(*G)->vertices[tail_vex].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		*(*G)->vertices[tail_vex].firstarc = *insert_arc;
		return OK;
	}

	//����(���ñ������ڽӻ�)
	for (temp = (*G)->vertices[tail_vex].firstarc;
		temp != NULL;temp = temp->nextarc) {//�����ڽӱ�
		if (temp->adjvex == head_vex) {//����ڱ��Ѿ�����
			return ERROR;
		}
		if (temp->nextarc == NULL) {//���뵽���һ���ڽӻ�
			temp->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
			*temp->nextarc = *insert_arc;
			return OK;
		}
	}

	return ERROR;
}
/**
 * �������ƣ�CreateGraph
 * ����������ͼG�ĵ�ַ��Vertex���㼯��VR�߹�ϵ��
 * �������ܣ����ݶ��㼯��߹�ϵ������һ��ͼ
 * ����ֵ���ɹ����췵��OK�����򷵻�ERROR
 **/
status CreateGraph(ALGraph *G, char *Vertex, Relation *VR)
{
    //��㼯ΪVertex ��VR�߹�ϵ ����һ��ͼ
    int i,j,k;//������
    int flag_1=0,flag_2=0;//��־�Ƿ��ҵ����
    ArcNode *insert_arc=NULL;//�����뻡

    if(*G){//��ͼ�Ѿ�����
        return ERROR;
    }

    //���򴴽�ͼ
    (*G)=(ALGraph)malloc(sizeof(ALNode));//����ͼͷ���
    (*G)->vexnum = strlen(Vertex);
    (*G)->arcnum = 0;
    //��ʼ���ڽӱ�
    for(i=0;i<MAX_VERTEX_NUM;i++){
        (*G)->vertices[i].data='\0';
        (*G)->vertices[i].firstarc=NULL;//��ʼ����һ���ڽӻ�
    }

    for(i=0;i<(*G)->vexnum;i++){//���㸳ֵ
        (*G)->vertices[i].data = *Vertex++;
    }

    for(;VR!=NULL;VR=VR->next){//�߸�ֵ
        flag_1=0;
        flag_2=0;
        printf("      ���ڹ�����(%c,%c)...",VR->tail,VR->head);

        for(j=0;j<(*G)->vexnum;j++){//�һ�β

            if((*G)->vertices[j].data==VR->tail){//���ҵ���β
                for(k=0;k<(*G)->vexnum;k++){//�һ�ͷ

                    if((*G)->vertices[k].data==VR->head){//�����ҵ���ͷ
                        //�����½��
                        insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                        insert_arc->adjvex = k;
                        insert_arc->nextarc = NULL;
                        insert_arc->info = VR->weight;

                        //����
                        if(Link(G,insert_arc,j,k)==OK){//���ɹ������
                            insert_arc -> adjvex = j;
                            Link(G,insert_arc,k,j);
                            (*G)->arcnum++;
                            printf("    ����ɹ�\n");
                        }
                        else{//������ʧ��
                            printf("    �ڽӱ�(%c,%c)�Ѿ����ڣ�����ʧ�ܣ��������˱߼�������\n",VR->tail,VR->head);
                        }

                        free(insert_arc);

                        flag_2=1;

                        break;
                    }
                    if(k==(*G)->vexnum-1&&flag_2==0){//�������δ�ҵ���ͷ
                        printf("    δ�ҵ�����%c\n",VR->head);
                    }

                }
                flag_1=1;

                break;
            }
            if(j==(*G)->vexnum-1&&flag_1==0){//�������δ�ҵ���β
                printf("    δ�ҵ�����%c\n",VR->tail);
            }

        }
    }

    return OK;
}

/**
 * �������ƣ�DestroyGraph
 * ����������ͼG�ĵ�ַ
 * �������ܣ�ɾ��ͼ
 * ����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
 **/
status DestroyGraph(ALGraph *G)
{
    //����ͼ
    ArcNode *temp1=NULL;
    ArcNode *temp2=NULL;
    int i;//������

    for(i=0;i<(*G)->vexnum;i++){//��������
        temp1=(*G)->vertices[i].firstarc;
        while(temp1){
            temp2=temp1->nextarc;
            free(temp1);
            temp1=temp2;
        }
    }
    free(*G);
    (*G)=NULL;
    return OK;
}

/**
 * �������ƣ�LocateVex
 * ����������ͼG������λ��num����������data
 * �������ܣ���num��������Ϊdata�Ķ����λ���
 * ����ֵ���ɹ��鵽�򷵻�OK�����򷵻�ERROR
 **/
status LocateVex(ALGraph G, int *num, VertexType data)
{
    //��������Ϊdata�Ķ����λ��num
    int i;//������
    for(i=0;i<G->vexnum;i++){//�������㼯
        if(data==G->vertices[i].data){//���ҵ�
            (*num)=i;
            return OK;
        }
    }
    //����δ�ҵ�
    return ERROR;
}

/**
 * �������ƣ�LocateVex
 * ����������ͼG������λ��num����������data
 * �������ܣ���data����λ��Ϊnum�Ķ��������
 * ����ֵ���ɹ��鵽�򷵻�OK�����򷵻�ERROR
 **/
status GetVex(ALGraph G, int num, VertexType *data)
{
    //����λ��Ϊnum�Ľ�������data

    //�ж�num�Ƿ�Ϸ�//num �� 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      ����Խ�磬num�Ƿ�\n");
        return ERROR;
    }

    //����data
    (*data) = G->vertices[num].data;
    return OK;
}

/**
 * �������ƣ�LocateVex
 * ����������ͼG������λ��num����������value
 * �������ܣ���valueΪλ��Ϊnum�Ķ��㸳ֵ
 * ����ֵ���ɹ���ֵ�򷵻�OK�����򷵻�ERROR
 **/
status PutVex(ALGraph *G, int num, VertexType value)
{
    //��λ��Ϊnum�Ľ�㸳ֵvalue

    //�ж�num�Ƿ�Ϸ�//num �� 0 ~ max-1
    if(num<0||num>=(*G)->vexnum) {
        printf("      ����Խ�磬num�Ƿ�\n");
        return ERROR;
    }

    //��ֵ
    (*G)->vertices[num].data=value;
    return OK;
}

/**
 * �������ƣ�FirstAdjVex
 * ����������ͼG������λ��num
 * �������ܣ�����λ��Ϊnum�Ķ���ĵ�һ�ڽӵ�
 * ����ֵ���ɹ��鵽�򷵻ص�һ�ڽӵ�ĵ�ַ�����򷵻�NULL
 **/
VNode* FirstAdjVex(ALGraph G,int num)
{
    //����λ��Ϊnum�Ķ���ĵ�һ�ڽӵ�

    //�ж�num�Ƿ�Ϸ�//num �� 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      ����Խ�磬�����λ��num�Ƿ�\n");
        return NULL;
    }

    //��num�����޵�һ�ڽӵ�
    if(!G->vertices[num].firstarc){
        printf("      %c�������ڽӵ�\n",G->vertices[num].data);
        return NULL;
    }

    //����num����ĵ�һ�ڽӵ�
    return &(G->vertices[G->vertices[num].firstarc->adjvex]);
}

/**
 * �������ƣ�NextAdjVex
 * ����������ͼG��v����λ��num��w����λ��num_w
 * �������ܣ�����λ��Ϊnum�Ķ���v��Զ���w����һ�ڽӵ�
 * ����ֵ���ɹ��鵽�򷵻���һ�ڽӵ�ĵ�ַ�����򷵻�NULL
 **/
VNode* NextAdjVex(ALGraph G,int num,int num_w)
{
    //����λ��Ϊnum�����w����һ���ڽӵ�

    //�ж�num��num_w�Ƿ�Ϸ�//num �� 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      ����Խ�磬v�����λ��num�Ƿ�\n");
        return NULL;
    }
    if(num_w<0||num_w>=G->vexnum) {
        printf("      ����Խ�磬w�����λ��num�Ƿ�\n");
        return NULL;
    }

    //��num�������ڽӵ�
    if(!G->vertices[num].firstarc){
        printf("      num�������ڽӵ�\n");
        return NULL;
    }

    ArcNode *temp=NULL;//���ڱ����ڽӱ�
    //��num������w���㲻�ڽ�
    for(temp=G->vertices[num].firstarc;temp!=NULL;temp=temp->nextarc){//�����ڽӱ�
        if(temp->adjvex==num_w){//���ҵ�w����
            if(temp->nextarc) return &(G->vertices[temp->nextarc->adjvex]);//������һ�ڽӵ㣬�򷵻�
            printf("      ��v�����ڽӵ�w��������ĩ�ڽӵ㣬����һ�ڽӵ�\n");
            return NULL;
        }
    }

    //δ�ҵ��ڽӵ�w
    printf("      w������v���㲻�ڽ�\n");
    return NULL;
}

/**
 * �������ƣ�InsertVex
 * ����������ͼG�ĵ�ַ����������data���߹ؼ�VR
 * �������ܣ���������Ϊdata�ĵ�����ڽӱ�����������صĶ���
 * ����ֵ���ɹ������򷵻�OK�����򷵻�ERROR
 **/
status InsertVex(ALGraph *G,VertexType data,Relation *VR)
{
    //���붥��

    //���޿ռ�
    if((*G)->vexnum==MAX_VERTEX_NUM){
        printf("      �ڽӱ�����\n");
        return ERROR;
    }

    int i;//������
    int num=(*G)->vexnum;
    for(i=0;i<num;i++){//ѭ����鶥���Ƿ��ظ�
        if((*G)->vertices[i].data==data){
            printf("      ���������ڽӱ��д��ڣ�����ʧ�ܣ�\n");
            return ERROR;
        }
    }

    //��ֵ����
    (*G)->vertices[num].data=data;
    //�������¶�����صı�
    int flag;//��¼�Ƿ��ҵ�����
    ArcNode *insert_arc=NULL;//��������±�

    for(;VR!=NULL;VR=VR->next){//�߸�ֵ
        flag=0;
        printf("      ���ڹ�����(%c,%c)...",VR->tail,VR->head);

        for(i=0;i<(*G)->vexnum;i++){//�һ�ͷ

            if((*G)->vertices[i].data==VR->head){//���ҵ���ͷ
                //�����½��
                insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                insert_arc->adjvex = i;
                insert_arc->nextarc = NULL;
                insert_arc->info = VR->weight;

                //����
                if(Link(G,insert_arc,num,i)==OK){//���ɹ������
                    insert_arc -> adjvex = num;
                    Link(G,insert_arc,i,num);
                    (*G)->arcnum++;
                    printf("    ����ɹ�\n");
                }
                else{//������ʧ��
                    printf("    �ڽӱ�(%c,%c)�Ѿ����ڣ�����ʧ�ܣ��������˱߼�������\n",VR->tail,VR->head);
                }

                free(insert_arc);
                flag=1;
                break;
            }
            if(i==(*G)->vexnum-1&&flag==0){//�������δ�ҵ���ͷ
                printf("    δ�ҵ�����%c\n",VR->head);
            }

        }
    }

    (*G)->vexnum++;
    return OK;
}

/**
 * �������ƣ�DeleteVex
 * ����������ͼG�ĵ�ַ������λ��num
 * �������ܣ�ɾ��λ��Ϊnum�Ķ���
 * ����ֵ���ɹ�ɾ���򷵻�OK�����򷵻�ERROR
 **/
status DeleteVex(ALGraph *G,int num)
{
    //ɾ������
    ArcNode *temp1=NULL;
    ArcNode *temp2=NULL;//�����ͷű߽��ռ�

    //�ͷſռ�(*G)->vertices[num].firstarc
    temp1=(*G)->vertices[num].firstarc;
    while(temp1){
        temp2=temp1->nextarc;
        free(temp1);
        temp1=temp2;
    }
    (*G)->vertices[num].firstarc=NULL;

    int i;//������
    ArcNode *temp=NULL;//���ڱ����ڽӱ�
    ArcNode *temp_del=NULL;//���ڴ�Ŵ�ɾ�����

    //ɾ����֮��صı�
    for(i=0;i<(*G)->vexnum;i++){//�������
        if((*G)->vertices[i].firstarc){//�����ڽӵ�
            temp=(*G)->vertices[i].firstarc;

            if (temp->adjvex == num) {//�����������ڽӱ�
				(*G)->vertices[i].firstarc = temp->nextarc;
				temp = (*G)->vertices[i].firstarc;
			}
			if (temp) {//��temp���ܽ���ɾ����Ϊ�գ���ɾ���������ڽӱ�
				if (temp->adjvex > num) temp->adjvex--;//�޸ĺ����߶�Ӧָ��
				for (;temp && temp->nextarc;temp = temp->nextarc) {//�����ڽӱ�
					if (temp->nextarc->adjvex == num) {//��temp->next�ڽ�num
						temp_del = temp->nextarc;
						temp->nextarc = temp->nextarc->nextarc;
						free(temp_del);
					}
					if (temp->nextarc) {//�������������һ�ڽӵ㣬�޸ĺ����߶�Ӧָ��
						if (temp->nextarc->adjvex > num) {
							temp->nextarc->adjvex--;
						}
					}
				}
			}

        }
    }

    //ɾ����
    for(i=num;i<(*G)->vexnum;i++){
        (*G)->vertices[i]=(*G)->vertices[i+1];
    }
    //�ͷſռ�(*G)->vertices[i].firstarc
    temp1=(*G)->vertices[i].firstarc;
    while(temp1){
        temp2=temp1->nextarc;
        free(temp1);
        temp1=temp2;
    }
    //�ÿ�
    (*G)->vertices[i].data='\0';
    (*G)->vertices[i].firstarc=NULL;
    (*G)->vexnum--;
    return OK;
}

/**
 * �������ƣ�InsertArc
 * ����������ͼG�ĵ�ַ���߹�ϵ��VR
 * �������ܣ����ձ߹�ϵ��VR���ڽӱ��в����
 * ����ֵ���ɹ������򷵻�OK�����򷵻�ERROR
 **/
status InsertArc(ALGraph *G,Relation *VR)
{
    //���뻡

    //��VR�߹�ϵ���ӱ�
    int i,j;//������
    int flag_1=0,flag_2=0;//��־�Ƿ��ҵ����
    ArcNode *insert_arc=NULL;//�����뻡���

    for(;VR!=NULL;VR=VR->next){//�߸�ֵ
        flag_1=0;
        flag_2=0;
        printf("  ���ڹ�����(%c,%c)...",VR->tail,VR->head);

        for(i=0;i<(*G)->vexnum;i++){//�һ�β

            if((*G)->vertices[i].data==VR->tail){//���ҵ���β
                for(j=0;j<(*G)->vexnum;j++){//�һ�ͷ

                    if((*G)->vertices[j].data==VR->head){//�����ҵ���ͷ
                        //�����½��
                        insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                        insert_arc->adjvex = j;
                        insert_arc->nextarc = NULL;
                        insert_arc->info = VR->weight;

                        //����
                        if(Link(G,insert_arc,i,j)==OK){//���ɹ������
                            insert_arc -> adjvex = i;
                            Link(G,insert_arc,j,i);
                            (*G)->arcnum++;
                            printf("    ����ɹ�\n");
                        }
                        else{//������ʧ��
                            printf("    �ڽӱ�(%c,%c)�Ѿ����ڣ�����ʧ�ܣ��������˱߼�������\n",VR->tail,VR->head);
                        }

                        free(insert_arc);

                        flag_2=1;

                        break;
                    }
                    if(j==(*G)->vexnum-1&&flag_2==0){//�������δ�ҵ���ͷ
                        printf("    δ�ҵ�����%c\n",VR->head);
                    }

                }
                flag_1=1;

                break;
            }
            if(i==(*G)->vexnum-1&&flag_1==0){//�������δ�ҵ���β
                printf("    δ�ҵ�����%c\n",VR->tail);
            }

        }
    }
    return OK;
}

/**
 * �������ƣ�DeleteVex
 * ����������ͼG�ĵ�ַ��v����λ��num_v��w����λ��num_w
 * �������ܣ�ɾ��v��w����֮����ڽӱ�
 * ����ֵ���ɹ�ɾ���򷵻�OK�����򷵻�ERROR
 **/
status DeleteArc(ALGraph *G,int num_v,int num_w)
{
    //ɾ����

    //�ж�num_v��num_w�Ƿ�Ϸ�
    if(num_v<0||num_v>=(*G)->vexnum) {
        printf("      ����Խ�磬�����λ��num_v�Ƿ�\n");
        return ERROR;
    }
    if(num_w<0||num_w>=(*G)->vexnum) {
        printf("      ����Խ�磬�����λ��num_w�Ƿ�\n");
        return ERROR;
    }

    //ɾ����
    int i;//������
    ArcNode *temp=NULL;//���ڱ����ڽӱ�
    ArcNode *temp_del=NULL;//���ڴ�Ŵ�ɾ�����

    //ɾ��v->w
    if((*G)->vertices[num_v].firstarc){//�����ڽӵ�
        temp=(*G)->vertices[num_v].firstarc;
        if(temp->adjvex==num_w){//�����ڽӵ�Ϊnum
            (*G)->vertices[num_v].firstarc=temp->nextarc;
            free(temp);
        }
        else{//��������ڽӱ�
            for(;temp->nextarc!=NULL;temp=temp->nextarc){//�����ڽӱ�
                if(temp->nextarc->adjvex==num_w && temp->nextarc->nextarc!=NULL){//��temp->next�ڽ�num�Ҳ�Ϊĩ�ڽӵ�
                    temp_del=temp->nextarc;
                    temp->nextarc=temp->nextarc->nextarc;
                    free(temp_del);
                    break;
                }
                if(temp->nextarc->adjvex==num_w && temp->nextarc->nextarc==NULL){//��temp->next�ڽ�num��Ϊĩ�ڽӵ�
                    free(temp->nextarc);
                    temp->nextarc=NULL;
                    break;
                }
            }
        }
    }
    //ɾ��w->v
    if((*G)->vertices[num_w].firstarc){//�����ڽӵ�
        temp=(*G)->vertices[num_w].firstarc;
        if(temp->adjvex==num_v){//�����ڽӵ�Ϊnum
            (*G)->vertices[num_w].firstarc=temp->nextarc;
            free(temp);
            (*G)->arcnum--;
            return OK;
        }
        else{//��������ڽӱ�
            for(;temp->nextarc!=NULL;temp=temp->nextarc){//�����ڽӱ�
                if(temp->nextarc->adjvex==num_v && temp->nextarc->nextarc!=NULL){//��temp->next�ڽ�num�Ҳ�Ϊĩ�ڽӵ�
                    temp_del=temp->nextarc;
                    temp->nextarc=temp->nextarc->nextarc;
                    free(temp_del);
                    (*G)->arcnum--;
                    return OK;
                }
                if(temp->nextarc->adjvex==num_v && temp->nextarc->nextarc==NULL){//��temp->next�ڽ�num��Ϊĩ�ڽӵ�
                    free(temp->nextarc);
                    temp->nextarc=NULL;
                    (*G)->arcnum--;
                    return OK;
                }
            }
        }
    }

    //��ɾ��ʧ��
    printf("      ����v��w֮�����ڽӱ�\n");
    return ERROR;
}

/**
 * DFSTraverse���Ӻ���
 **/
void DFS(ALGraph G, int i, int *visited)
{
    //���������������ͼ�ĵݹ�ʵ��
    ArcNode *temp=NULL;

    visited[i] = 1;
    printf("%c ", G->vertices[i].data);
    temp = G->vertices[i].firstarc;
    while (temp != NULL)
    {
        if (!visited[temp->adjvex]){
            DFS(G, temp->adjvex, visited);
        }
        temp = temp->nextarc;
    }
}
/**
 * �������ƣ�DFSTraverse
 * ����������ͼG
 * �������ܣ�������ȱ���ͼ
 * ����ֵ���ɹ������򷵻�OK�����򷵻�ERROR
 **/
status DFSTraverse(ALGraph G)
{
    //���������������ͼ
    int i;                             //������
    int visited[MAX_VERTEX_NUM];       //������ʱ��

    for (i = 0; i < G->vexnum; i++){//��ʼ�����ʱ��
        visited[i] = 0;
    }

    printf("      DFS: ");
    for (i = 0; i < G->vexnum; i++){
        if (!visited[i]){
            DFS(G, i, visited);
        }
    }
    printf("\n");
    return OK;
}

/**
 * �������ƣ�BFSTraverse
 * ����������ͼG
 * �������ܣ�������ȱ���ͼ
 * ����ֵ���ɹ������򷵻�OK�����򷵻�ERROR
 **/
status BFSTraverse(ALGraph G)
{
    //���������������
    int head = 0;
    int rear = 0;
    int queue[MAX_VERTEX_NUM];     //�������
    int visited[MAX_VERTEX_NUM];   //������ʱ��
    int i, j, k;        //������
    ArcNode *temp=NULL;

    for (i = 0; i < G->vexnum; i++){//��ʼ�����ʱ��
        visited[i] = 0;
    }

    printf("      BFS: ");
    for (i = 0; i < G->vexnum; i++){
        if (!visited[i]){
            visited[i] = 1;
            printf("%c ", G->vertices[i].data);
            queue[rear++] = i;  //ͷ��������
        }
        while (head != rear) {
            j = queue[head++];  //������
            temp = G->vertices[j].firstarc;
            while (temp != NULL){
                k = temp->adjvex;
                if (!visited[k]){
                    visited[k] = 1;
                    printf("%c ", G->vertices[k].data);
                    queue[rear++] = k; //δ���ʵ��ܱ߽�������
                }
                temp = temp->nextarc;
            }
        }
    }
    printf("\n");

    return OK;
}

/**
 * �������ƣ�LoadList
 * ����������ͼG�ĵ�ַ���ļ���filename
 * �������ܣ����ݼ��أ����ļ������ݶ��룬���ǵ�ǰͼ
 * ����ֵ�����سɹ�����OK������ʧ�ܷ���ERROR
 **/
status LoadFile(ALGraph *G,char *filename)
{
    ALGraph G_temp=NULL;
    char Vertex[MAX];//���㼯������
    Relation *VR;//�߹�ϵ������
    Vertex[0]='\0';//��ʼ��
    VR=(Relation*)malloc(sizeof(Relation));
    VR->next=NULL;//��ʼ��
    FILE *fp;//�ļ�ָ��
    fp = fopen(filename, "r");
    if(fp==NULL) {
        printf("�ļ������ڣ�\n");
        return ERROR;
    }

    //���ļ������ݶ���ϵͳ
    fscanf(fp,"%s\r\n",Vertex);//��ȡvertex
    //����VR
    char tail,head;
    int weight;
    Relation *temp=VR;//���ڱ���
    Relation *insert=NULL;//��������
    while(fscanf(fp,"%c %c %d\r\n",&tail,&head,&weight)!=EOF){
        //�½�㸳ֵ
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //����
        temp->next=insert;
        temp=temp->next;
    }

    printf("        ���Խ���ͼ��\n");
    if(CreateGraph(&G_temp,Vertex,VR->next)==OK){//���ļ��������ܹ���ͼ���ǵ�ǰͼ
        printf("        �ļ������ݷ���Ҫ�󣬸��ǵ�ǰͼ��\n");
        DestroyGraph(G);
        CreateGraph(G,Vertex,VR->next);
        fclose(fp);
        return OK;
    }
    else{
        printf("      �ļ������ݸ�ʽ���󣬶�ȡʧ�ܣ�\n");
    }
    fclose(fp);
    return ERROR;
}

/**
 * �������ƣ�SaveAsFile
 * ����������ͼG�ĵ�ַ���ļ���filename
 * �������ܣ����ݱ��棬��ͼ�����ݱ������ļ�
 * ����ֵ������ɹ�����OK������ʧ�ܷ���ERROR
 **/
status SaveAsFile(ALGraph G,char *filename)
{
    int head = 0;
    int rear = 0;
    int queue[MAX_VERTEX_NUM];     //�������
    int visited[MAX_VERTEX_NUM];   //������ʱ��
    int i, j, k;        //������
    char VR[MAX_VERTEX_NUM];//���㼯
    ArcNode *temp=NULL;
    FILE *fp;
    fp = fopen(filename, "wb+");

    //���㼯�����ļ�
    for(i=0;i<MAX_VERTEX_NUM;i++){
        VR[i]=G->vertices[i].data;
    }
    fprintf(fp, "%s\r\n", VR);

    //��ȱ�����ͼ��Ԫ��ת��Ϊ�����ʽ�������ļ�
    for (i = 0; i < G->vexnum; i++){//��ʼ�����ʱ��
        visited[i] = 0;
    }
    for (i = 0; i < G->vexnum; i++){
        if (!visited[i]){
            queue[rear++] = i;  //ͷ��������
        }
        while (head != rear) {
            j = queue[head++];  //������
            visited[j] = 1;
            temp = G->vertices[j].firstarc;
            while (temp != NULL){
                k = temp->adjvex;
                if (!visited[k]){
                    fprintf(fp,"%c %c %d\r\n",G->vertices[j].data,G->vertices[k].data,temp->info);
                    queue[rear++] = k; //δ���ʵ��ܱ߽�������
                }
                temp = temp->nextarc;
            }
        }
    }

    fclose(fp);
    return OK;
}

/**
 * �������ƣ�MulList
 * ����������ͼG�ĵ�ַ����ͼ��ͷM�ĵ�ַ����ǰͼ���list_num_cur�����л�����ͼ���list_num
 * �������ܣ��л�����ͼ��
 * ����ֵ���ɹ��л�����OK�����򷵻�ERROR
 **/
status MulList(ALGraph *G,MulNode *M,int list_num_cur,int list_num){
    //�л�����ͼ����Ŀ��ͼ���������½�
    MulNode *mul_temp=NULL;//���ڱ�����ͼ�ṹ
    MulNode *mul_new=NULL;//�����½���ͼ���
    //�洢ͼ
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//����ͼ�ṹ�еĶ�Ӧ�ڵ㸳ֵ����������
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*G);
            break;
        }
    }

    //�л�ͼ��Ϊͼͷָ��G��ֵ��
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//��ѯ��ͼ�ṹ�еĶ�Ӧ�ڵ㣬�л�������
        if(mul_temp->next->list_num==list_num){//����ѯ�ɹ�������ͼ
            (*G) = mul_temp->next->list_head;
            return OK;
        }
    }
    //����ѯʧ�ܣ��ڶ�ͼ�ṹ���½�ͼ����ʱmul_temp->nextָ���Ѿ�ָ������β��NULL
    mul_new = (MulNode *)malloc(sizeof(MulNode));
    if (mul_new==NULL) return OVERFLOW;   //����ռ�ʧ��

    mul_new -> list_num = list_num;//��ֵ����
    mul_new -> list_head = NULL;//�±�ͷ�ڵ��ÿ�
    mul_new -> next = NULL;//�½ڵ�next�ÿ�

    mul_temp -> next = mul_new;//Ϊ�½ڵ㸳ֵ
    M->list_num++;//��¼������+1

    (*G) = mul_new -> list_head;

    return ERROR;
}
