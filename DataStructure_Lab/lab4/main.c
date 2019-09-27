#include"graph.h"
void main(void){

    MulNode *MulList_head=NULL;//多表表头,其data域存储多表个数
    MulNode *MulList_temp=NULL;//用于遍历多表结点输出所有表序
    //初始化多表结构
    MulList_head = (MulNode*)malloc(sizeof(MulNode));
    MulList_head->list_num= 1;//表头data域存储多表个数
    MulList_head->list_head=NULL;
    MulList_head->next=(MulNode*)malloc(sizeof(MulNode));//新建表1
    MulList_head->next->list_num=1;//表序为1
    MulList_head->next->list_head=NULL;
    MulList_head->next->next=NULL;

    int list_num=1;//图编号（名字）
    int list_num_cur=0;//记录当前图序号
    int flag;//多表操作中记录函数返回值

    ALGraph G=NULL;//当前图头结点

    char Vertex[MAX];//顶点集合
    Vertex[0]='\0';//初始化
    Relation *VR=NULL;//VR边关系的头结点

    int i,j,k,flag_c;//计数器，用于检验vertex顶点集是否重复
    int num;//顶点v的位序num
    int num_w;//顶点w的位序num
    char filename[MAX];//文件名称
    VertexType data;//返回数据
    VertexType value;//用于赋值的顶点值
    VNode *temp=NULL;//返回查找到的顶点

    int op=1;

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Graph On Adjacency List \n");
        printf("      当前操作的图序号为%d\n",list_num);
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
        printf("    请选择你的操作[0~16]:");
        fflush(stdin);
        scanf("%d",&op);

    switch(op){
        case 1:
            //创建图
            if(G) {
                printf("      图已创建，创建失败！\n");
                getchar();
            }
            else{
                //读入顶点集
                printf("      请输入顶点集(长度不大于%d的字符串)\n      ",MAX_VERTEX_NUM);
                scanf("%s",Vertex);
                getchar();
                fflush(stdin);

                //Vertex序列中检查顶点个数
                k=strlen(Vertex);//顶点个数
                if(k>MAX_VERTEX_NUM){//若输入顶点过多
                    printf("      输入顶点超出上限！将返回主菜单\n");
                    Vertex[0]='\0';
                    getchar();
                    break;
                }

                if(Vertex[0]=='\0'){//顶点集格式有误
                    printf("      顶点集输入格式有误！将返回主菜单\n");
                    getchar();
                    break;
                }

                //Vertex序列中检查重复顶点
                flag_c=0;//标记是否检查到重复顶点
                for(i=0;i<k-1;i++){//双重循环检查重复顶点
                    for(j=i+1;j<k;j++){
                        if(Vertex[i]==Vertex[j]){//检查到重复顶点
                            flag_c=1;
                            break;
                        }
                    }
                    if(flag_c) break;
                }

                if(flag_c){//若顶点集中有重复顶点
                    printf("      顶点集中含有重复顶点，输入有误！将返回主菜单\n");
                    Vertex[0]='\0';
                }
                else{//继续读取边关系
                    ScanfVR(&VR);
                    if(CreateGraph(&G,Vertex,VR->next)==OK) printf("\n      图创建完成！\n");
                    else printf("      存储空间不足，创建失败！\n");
                }
            }
            getchar();
            break;
        case 2:
            //销毁
            if(!G) printf("      图未创建！\n");
            else{
                if(DestroyGraph(&G)==OK) printf("      图销毁成功！\n");
            }
            getchar();getchar();
            break;
        case 3:
            //查找data的位置信息
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入数据data，将为您返回该顶点的位序\n\n");
                getchar();
                printf("      data：");
                scanf("%c",&data);
                if(LocateVex(G,&num,data)==OK) printf("      图中顶点%c在邻接表中的位序为%d",data,num);
                else printf("      图中未找到data为%c的顶点！\n",data);
            }
            getchar();getchar();
            break;
        case 4:
            //查找对应位置的data
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入位序num，将为您返回该顶点数据\n\n");
                printf("      num：");
                scanf("%d",&num);
                if(GetVex(G,num,&data)==OK) printf("      图中位序为%d的顶点的数据为%c\n",num,data);
                else printf("      不存在位序为%d的顶点！\n",num);
            }
            getchar();getchar();
            break;
        case 5:
            //对应位置顶点赋值为value
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入位序num与数据value，将为该顶点赋值\n\n");
                printf("      num：");
                scanf("%d",&num);
                getchar();
                printf("      value：");
                scanf("%c",&value);
                if(PutVex(&G,num,value)==OK) printf("      图中位序为%d的顶点的值更改成功\n",num);
                else printf("      不存在位序为%d的结点！\n",num);
            }
            getchar();getchar();
            break;

        case 6:
            //获得num顶点的第一邻接点
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入顶点v的位序num，将为您返回该顶点的第一邻接点\n\n");
                printf("      (顶点v)num：");
                scanf("%d",&num);
                temp=FirstAdjVex(G,num);
                if(temp!=NULL) printf("      图中位序为%d的顶点的第一邻接点的位序num为%d，数据data为%c\n",num,G->vertices[num].firstarc->adjvex,temp->data);
                else printf("      查找失败！\n");
            }
            temp=NULL;//置空暂存结点
            getchar();getchar();
            break;
        case 7:
            //获得num顶点相对于num_w的下一邻接点
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入顶点v与w的位序num，将为您返回v结点相对u顶点的下一邻接点\n\n");
                printf("      (顶点v)num：");
                scanf("%d",&num);
                printf("      (顶点w)num：");
                scanf("%d",&num_w);
                temp=NextAdjVex(G,num,num_w);
                if(temp!=NULL) printf("      图中位序为%d的顶点v相对w的下一邻接点的数据data为%c\n",num,temp->data);
                else printf("      查找失败！\n");
            }
            temp=NULL;//置空暂存结点
            getchar();getchar();
            break;
        case 8:
            //插入顶点
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入顶点数据，将为您在邻接表中插入该顶点\n\n");
                printf("      data：");
                getchar();
                scanf("%c",&data);
                getchar();
                ScanfVR_insert(&VR,data);//读取边关系

                if(InsertVex(&G,data,VR->next)==OK) printf("      插入顶点成功！\n");
                else printf("      插入顶点失败！\n");
            }
            getchar();
            break;
        case 9:
            //删除顶点
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入顶点数据data，将为您删除该顶点\n\n");
                printf("      data：");
                getchar();
                scanf("%c",&data);
                if(LocateVex(G,&num,data)==OK){
                    if(DeleteVex(&G,num)==OK) printf("      删除顶点成功！\n");
                    else printf("      删除顶点失败！\n");
                }
                else{
                    printf("      在邻接表内未查询到值为%c的顶点！\n",data);
                }
            }
            getchar();getchar();
            break;
        case 10:
            //插入弧
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                getchar();
                ScanfVR(&VR);
                if(InsertArc(&G,VR->next)==OK) printf("      插入完成！\n");
                else printf("      插入失败！\n");
            }
            getchar();
            break;
        case 11:
            //删除弧
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      请输入顶点v与w的位序num，将为您删除链接他们的弧\n\n");
                printf("      (顶点v)num：");
                scanf("%d",&num);
                getchar();
                printf("      (顶点w)num：");
                scanf("%d",&num_w);
                if(DeleteArc(&G,num,num_w)==OK) printf("      删除弧成功！\n");
                else printf("      删除弧失败！\n");
            }
            getchar();getchar();
            break;
        case 12:
            //DFS
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      图的深度优先遍历结果：\n");
                printf("--------------------------------------------\n");
                DFSTraverse(G);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 13:
            //BFS
            if(!G) printf("      图未创建！\n");//图不存在
            else{
                printf("      图的广度优先遍历结果：\n");
                printf("--------------------------------------------\n");
                BFSTraverse(G);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 14:
            //读取文件
            if(!G){
                printf("      图未创建！\n");//图不存在
                getchar();
            }
            else{
                printf("      将从文件中读取数据并覆盖当前图.\n      请输入要读取的文件名: ");getchar();
                gets(filename);
                if(LoadFile(&G,filename)==OK) printf("      文件读取成功！\n");
                else printf("      文件读取失败！\n");
            }
            getchar();
            break;
        case 15:
            //存储文件
            if(!G){
                printf("      图未创建！\n");//图不存在
                getchar();
            }
            else{
                printf("      将图中数据保存(写)为文件\n      请输入要写入的文件名: ");getchar();
                gets(filename);
                if(SaveAsFile(G,filename)==OK) printf("      文件写入成功！\n");
            }
            getchar();
            break;
        case 16:
            list_num_cur=list_num;//记录当前图序以存储数据
            printf("      请输入要切换到的图序号：");
            scanf("%d",&list_num);

            flag=MulList(&G,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      切换成功，当前操作图为图%d\n",list_num);
            else if(flag==ERROR) printf("      图%d不存在，已为您新建图%d并切换(未初始化)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//新图创建失败
                printf("      空间不足，图创建失败！\n");
                list_num=list_num_cur;//当前图序回退至换表前
            }

            //输出所有图序号
            printf("\n------------------- all list --------------------\n");
            printf("      当前共有%d个图可供操作\n      其序号为(依创建时间排序)：\n      ",MulList_head->list_num);
            for(MulList_temp=MulList_head;MulList_temp->next!=NULL;MulList_temp=MulList_temp->next){//输出所有表序
                printf("%d ",MulList_temp->next->list_num);
            }
            printf("\n---------------------- end ----------------------\n");

            getchar();getchar();
            break;
        case 0:
            break;

        }//end of switch

    }//end of while

    printf("\n      欢迎下次再使用本系统！\n");
}//end of main()

/**
 * 函数名称：ScanfVR
 * 函数功能：用于读取VR边关系集的子函数
 **/
void ScanfVR(Relation **VR)
{
    //读取边关系VR
    char tail,head;
    int weight=-1;
    *VR=(Relation*)malloc(sizeof(Relation));
    (*VR)->next=NULL;
    Relation *temp=*VR;//用于遍历
    Relation *insert=NULL;//待插入结点

    printf("\n    Tips：不支持构建单边环及负权边\n");
    printf("          样例输入：a b 6\n");
    printf("    请输入欲链接的顶点值与其边的权重,输入文件尾停止读取\n      ");
    while(scanf("%c %c %d",&tail,&head,&weight)!=EOF){
        if(tail=='\n'||tail==' '||head=='\n'||head==' '||weight<=0||tail==head){//若读取格式有误
            printf("      输入格式有误，将跳过此组输入\n");
            printf("    请输入欲链接的结点值与其边的权重,输入文件尾停止读取\n      ");
            fflush(stdin);
            continue;
        }
        getchar();
        //新结点赋值
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //链接
        temp->next=insert;
        temp=temp->next;
        printf("    请输入欲链接的结点值与其边的权重,输入文件尾停止读取\n      ");

        fflush(stdin);//清空输入流
        weight=-1;//重置权
    }
    printf("\n");
}

/**
 * 函数名称：ScanfVR_insert
 * 函数功能：用于读取VR边关系集的子函数
 **/
void ScanfVR_insert(Relation **VR,char tail)
{
    //读取边关系VR
    char head;
    int weight=-1;
    *VR=(Relation*)malloc(sizeof(Relation));
    (*VR)->next=NULL;
    Relation *temp=*VR;//用于遍历
    Relation *insert=NULL;//待插入结点

    printf("\n    Tips：不支持构建单边环及负权边\n");
    printf("          样例输入：b 6\n");
    printf("    请输入欲与顶点%c链接的顶点值与其边的权重,输入文件尾停止读取\n      ",tail);
    while(scanf("%c %d",&head,&weight)!=EOF){
        if(head=='\n'||head==' '||weight<=0||tail==head){//若读取格式有误
            printf("      输入格式有误，将跳过此组输入\n");
            printf("    请输入欲链接的结点值与其边的权重,输入文件尾停止读取\n      ");
            fflush(stdin);
            continue;
        }
        getchar();
        //新结点赋值
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //链接
        temp->next=insert;
        temp=temp->next;
        printf("    请输入欲链接的结点值与其边的权重,输入文件尾停止读取\n      ");

        fflush(stdin);//清空输入流
        weight=-1;//重置权
    }
    printf("\n");
}

/**
 * 函数名称：Link
 * 函数功能：用于根据位序链接邻接表中两个顶点
 * 返回值：成功链接返回OK，否则返回ERROR
 **/
status Link(ALGraph *G, ArcNode *insert_arc, int tail_vex, int head_vex)
{
	//在邻接表中用弧insert_arc链接(tail_vex,head_vex)
	ArcNode *temp = NULL;//用于遍历邻接弧

	if (!(*G)->vertices[tail_vex].firstarc) {//若弧尾无邻接弧
		(*G)->vertices[tail_vex].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		*(*G)->vertices[tail_vex].firstarc = *insert_arc;
		return OK;
	}

	//否则(若该边已有邻接弧)
	for (temp = (*G)->vertices[tail_vex].firstarc;
		temp != NULL;temp = temp->nextarc) {//遍历邻接边
		if (temp->adjvex == head_vex) {//如果邻边已经存在
			return ERROR;
		}
		if (temp->nextarc == NULL) {//插入到最后一个邻接弧
			temp->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
			*temp->nextarc = *insert_arc;
			return OK;
		}
	}

	return ERROR;
}
/**
 * 函数名称：CreateGraph
 * 函数参数：图G的地址，Vertex顶点集，VR边关系集
 * 函数功能：根据顶点集与边关系集构造一个图
 * 返回值：成功构造返回OK，否则返回ERROR
 **/
status CreateGraph(ALGraph *G, char *Vertex, Relation *VR)
{
    //结点集为Vertex 以VR边关系 创建一个图
    int i,j,k;//计数器
    int flag_1=0,flag_2=0;//标志是否找到结点
    ArcNode *insert_arc=NULL;//代插入弧

    if(*G){//若图已经存在
        return ERROR;
    }

    //否则创建图
    (*G)=(ALGraph)malloc(sizeof(ALNode));//创建图头结点
    (*G)->vexnum = strlen(Vertex);
    (*G)->arcnum = 0;
    //初始化邻接表
    for(i=0;i<MAX_VERTEX_NUM;i++){
        (*G)->vertices[i].data='\0';
        (*G)->vertices[i].firstarc=NULL;//初始化第一条邻接弧
    }

    for(i=0;i<(*G)->vexnum;i++){//顶点赋值
        (*G)->vertices[i].data = *Vertex++;
    }

    for(;VR!=NULL;VR=VR->next){//边赋值
        flag_1=0;
        flag_2=0;
        printf("      正在构建边(%c,%c)...",VR->tail,VR->head);

        for(j=0;j<(*G)->vexnum;j++){//找弧尾

            if((*G)->vertices[j].data==VR->tail){//若找到弧尾
                for(k=0;k<(*G)->vexnum;k++){//找弧头

                    if((*G)->vertices[k].data==VR->head){//且若找到弧头
                        //创建新结点
                        insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                        insert_arc->adjvex = k;
                        insert_arc->nextarc = NULL;
                        insert_arc->info = VR->weight;

                        //插入
                        if(Link(G,insert_arc,j,k)==OK){//若成功插入边
                            insert_arc -> adjvex = j;
                            Link(G,insert_arc,k,j);
                            (*G)->arcnum++;
                            printf("    插入成功\n");
                        }
                        else{//若插入失败
                            printf("    邻接边(%c,%c)已经存在，构建失败！将跳过此边继续创建\n",VR->tail,VR->head);
                        }

                        free(insert_arc);

                        flag_2=1;

                        break;
                    }
                    if(k==(*G)->vexnum-1&&flag_2==0){//遍历完成未找到弧头
                        printf("    未找到顶点%c\n",VR->head);
                    }

                }
                flag_1=1;

                break;
            }
            if(j==(*G)->vexnum-1&&flag_1==0){//遍历完成未找到弧尾
                printf("    未找到顶点%c\n",VR->tail);
            }

        }
    }

    return OK;
}

/**
 * 函数名称：DestroyGraph
 * 函数参数：图G的地址
 * 函数功能：删除图
 * 返回值：成功删除返回OK，否则返回ERROR
 **/
status DestroyGraph(ALGraph *G)
{
    //销毁图
    ArcNode *temp1=NULL;
    ArcNode *temp2=NULL;
    int i;//计数器

    for(i=0;i<(*G)->vexnum;i++){//遍历顶点
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
 * 函数名称：LocateVex
 * 函数参数：图G，顶点位序num，顶点数据data
 * 函数功能：用num返回数据为data的顶点的位序号
 * 返回值：成功查到则返回OK，否则返回ERROR
 **/
status LocateVex(ALGraph G, int *num, VertexType data)
{
    //返回数据为data的顶点的位置num
    int i;//计数器
    for(i=0;i<G->vexnum;i++){//遍历顶点集
        if(data==G->vertices[i].data){//若找到
            (*num)=i;
            return OK;
        }
    }
    //否则未找到
    return ERROR;
}

/**
 * 函数名称：LocateVex
 * 函数参数：图G，顶点位序num，顶点数据data
 * 函数功能：用data返回位序为num的顶点的数据
 * 返回值：成功查到则返回OK，否则返回ERROR
 **/
status GetVex(ALGraph G, int num, VertexType *data)
{
    //返回位序为num的结点的数据data

    //判断num是否合法//num ∈ 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      访问越界，num非法\n");
        return ERROR;
    }

    //传出data
    (*data) = G->vertices[num].data;
    return OK;
}

/**
 * 函数名称：LocateVex
 * 函数参数：图G，顶点位序num，顶点数据value
 * 函数功能：用value为位序为num的顶点赋值
 * 返回值：成功赋值则返回OK，否则返回ERROR
 **/
status PutVex(ALGraph *G, int num, VertexType value)
{
    //对位序为num的结点赋值value

    //判断num是否合法//num ∈ 0 ~ max-1
    if(num<0||num>=(*G)->vexnum) {
        printf("      访问越界，num非法\n");
        return ERROR;
    }

    //赋值
    (*G)->vertices[num].data=value;
    return OK;
}

/**
 * 函数名称：FirstAdjVex
 * 函数参数：图G，顶点位序num
 * 函数功能：查找位序为num的顶点的第一邻接点
 * 返回值：成功查到则返回第一邻接点的地址，否则返回NULL
 **/
VNode* FirstAdjVex(ALGraph G,int num)
{
    //返回位序为num的顶点的第一邻接点

    //判断num是否合法//num ∈ 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      访问越界，顶点的位序num非法\n");
        return NULL;
    }

    //若num顶点无第一邻接点
    if(!G->vertices[num].firstarc){
        printf("      %c顶点无邻接点\n",G->vertices[num].data);
        return NULL;
    }

    //返回num顶点的第一邻接点
    return &(G->vertices[G->vertices[num].firstarc->adjvex]);
}

/**
 * 函数名称：NextAdjVex
 * 函数参数：图G，v顶点位序num，w顶点位序num_w
 * 函数功能：查找位序为num的顶点v相对顶点w的下一邻接点
 * 返回值：成功查到则返回下一邻接点的地址，否则返回NULL
 **/
VNode* NextAdjVex(ALGraph G,int num,int num_w)
{
    //返回位序为num的相对w的下一个邻接点

    //判断num与num_w是否合法//num ∈ 0 ~ max-1
    if(num<0||num>=G->vexnum) {
        printf("      访问越界，v顶点的位序num非法\n");
        return NULL;
    }
    if(num_w<0||num_w>=G->vexnum) {
        printf("      访问越界，w顶点的位序num非法\n");
        return NULL;
    }

    //若num顶点无邻接点
    if(!G->vertices[num].firstarc){
        printf("      num顶点无邻接点\n");
        return NULL;
    }

    ArcNode *temp=NULL;//用于遍历邻接边
    //若num顶点与w顶点不邻接
    for(temp=G->vertices[num].firstarc;temp!=NULL;temp=temp->nextarc){//遍历邻接边
        if(temp->adjvex==num_w){//若找到w顶点
            if(temp->nextarc) return &(G->vertices[temp->nextarc->adjvex]);//若有下一邻接点，则返回
            printf("      与v顶点邻接的w顶点已是末邻接点，无下一邻接点\n");
            return NULL;
        }
    }

    //未找到邻接点w
    printf("      w顶点与v顶点不邻接\n");
    return NULL;
}

/**
 * 函数名称：InsertVex
 * 函数参数：图G的地址，顶点数据data，边关集VR
 * 函数功能：插入数据为data的点进入邻接表并链接与其相关的顶点
 * 返回值：成功插入则返回OK，否则返回ERROR
 **/
status InsertVex(ALGraph *G,VertexType data,Relation *VR)
{
    //插入顶点

    //若无空间
    if((*G)->vexnum==MAX_VERTEX_NUM){
        printf("      邻接表已满\n");
        return ERROR;
    }

    int i;//计数器
    int num=(*G)->vexnum;
    for(i=0;i<num;i++){//循环检查顶点是否重复
        if((*G)->vertices[i].data==data){
            printf("      顶点已在邻接表中存在，插入失败！\n");
            return ERROR;
        }
    }

    //赋值顶点
    (*G)->vertices[num].data=data;
    //链接与新顶点相关的边
    int flag;//记录是否找到顶点
    ArcNode *insert_arc=NULL;//待插入的新边

    for(;VR!=NULL;VR=VR->next){//边赋值
        flag=0;
        printf("      正在构建边(%c,%c)...",VR->tail,VR->head);

        for(i=0;i<(*G)->vexnum;i++){//找弧头

            if((*G)->vertices[i].data==VR->head){//若找到弧头
                //创建新结点
                insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                insert_arc->adjvex = i;
                insert_arc->nextarc = NULL;
                insert_arc->info = VR->weight;

                //插入
                if(Link(G,insert_arc,num,i)==OK){//若成功插入边
                    insert_arc -> adjvex = num;
                    Link(G,insert_arc,i,num);
                    (*G)->arcnum++;
                    printf("    插入成功\n");
                }
                else{//若插入失败
                    printf("    邻接边(%c,%c)已经存在，构建失败！将跳过此边继续创建\n",VR->tail,VR->head);
                }

                free(insert_arc);
                flag=1;
                break;
            }
            if(i==(*G)->vexnum-1&&flag==0){//遍历完成未找到弧头
                printf("    未找到顶点%c\n",VR->head);
            }

        }
    }

    (*G)->vexnum++;
    return OK;
}

/**
 * 函数名称：DeleteVex
 * 函数参数：图G的地址，顶点位置num
 * 函数功能：删除位置为num的顶点
 * 返回值：成功删除则返回OK，否则返回ERROR
 **/
status DeleteVex(ALGraph *G,int num)
{
    //删除顶点
    ArcNode *temp1=NULL;
    ArcNode *temp2=NULL;//用于释放边结点空间

    //释放空间(*G)->vertices[num].firstarc
    temp1=(*G)->vertices[num].firstarc;
    while(temp1){
        temp2=temp1->nextarc;
        free(temp1);
        temp1=temp2;
    }
    (*G)->vertices[num].firstarc=NULL;

    int i;//计数器
    ArcNode *temp=NULL;//用于遍历邻接边
    ArcNode *temp_del=NULL;//用于存放待删除结点

    //删除与之相关的边
    for(i=0;i<(*G)->vexnum;i++){//遍历结点
        if((*G)->vertices[i].firstarc){//若有邻接点
            temp=(*G)->vertices[i].firstarc;

            if (temp->adjvex == num) {//单独处理首邻接边
				(*G)->vertices[i].firstarc = temp->nextarc;
				temp = (*G)->vertices[i].firstarc;
			}
			if (temp) {//（temp可能进行删除后为空）若删除后仍有邻接边
				if (temp->adjvex > num) temp->adjvex--;//修改后续边对应指向
				for (;temp && temp->nextarc;temp = temp->nextarc) {//遍历邻接边
					if (temp->nextarc->adjvex == num) {//若temp->next邻接num
						temp_del = temp->nextarc;
						temp->nextarc = temp->nextarc->nextarc;
						free(temp_del);
					}
					if (temp->nextarc) {//若处理后仍有下一邻接点，修改后续边对应指向
						if (temp->nextarc->adjvex > num) {
							temp->nextarc->adjvex--;
						}
					}
				}
			}

        }
    }

    //删除点
    for(i=num;i<(*G)->vexnum;i++){
        (*G)->vertices[i]=(*G)->vertices[i+1];
    }
    //释放空间(*G)->vertices[i].firstarc
    temp1=(*G)->vertices[i].firstarc;
    while(temp1){
        temp2=temp1->nextarc;
        free(temp1);
        temp1=temp2;
    }
    //置空
    (*G)->vertices[i].data='\0';
    (*G)->vertices[i].firstarc=NULL;
    (*G)->vexnum--;
    return OK;
}

/**
 * 函数名称：InsertArc
 * 函数参数：图G的地址，边关系集VR
 * 函数功能：按照边关系集VR在邻接表中插入边
 * 返回值：成功插入则返回OK，否则返回ERROR
 **/
status InsertArc(ALGraph *G,Relation *VR)
{
    //插入弧

    //以VR边关系链接边
    int i,j;//计数器
    int flag_1=0,flag_2=0;//标志是否找到结点
    ArcNode *insert_arc=NULL;//待插入弧结点

    for(;VR!=NULL;VR=VR->next){//边赋值
        flag_1=0;
        flag_2=0;
        printf("  正在构建边(%c,%c)...",VR->tail,VR->head);

        for(i=0;i<(*G)->vexnum;i++){//找弧尾

            if((*G)->vertices[i].data==VR->tail){//若找到弧尾
                for(j=0;j<(*G)->vexnum;j++){//找弧头

                    if((*G)->vertices[j].data==VR->head){//且若找到弧头
                        //创建新结点
                        insert_arc = (ArcNode *)malloc(sizeof(ArcNode));
                        insert_arc->adjvex = j;
                        insert_arc->nextarc = NULL;
                        insert_arc->info = VR->weight;

                        //插入
                        if(Link(G,insert_arc,i,j)==OK){//若成功插入边
                            insert_arc -> adjvex = i;
                            Link(G,insert_arc,j,i);
                            (*G)->arcnum++;
                            printf("    插入成功\n");
                        }
                        else{//若插入失败
                            printf("    邻接边(%c,%c)已经存在，构建失败！将跳过此边继续创建\n",VR->tail,VR->head);
                        }

                        free(insert_arc);

                        flag_2=1;

                        break;
                    }
                    if(j==(*G)->vexnum-1&&flag_2==0){//遍历完成未找到弧头
                        printf("    未找到顶点%c\n",VR->head);
                    }

                }
                flag_1=1;

                break;
            }
            if(i==(*G)->vexnum-1&&flag_1==0){//遍历完成未找到弧尾
                printf("    未找到顶点%c\n",VR->tail);
            }

        }
    }
    return OK;
}

/**
 * 函数名称：DeleteVex
 * 函数参数：图G的地址，v顶点位置num_v，w顶点位置num_w
 * 函数功能：删除v，w顶点之间的邻接边
 * 返回值：成功删除则返回OK，否则返回ERROR
 **/
status DeleteArc(ALGraph *G,int num_v,int num_w)
{
    //删除弧

    //判断num_v与num_w是否合法
    if(num_v<0||num_v>=(*G)->vexnum) {
        printf("      访问越界，顶点的位序num_v非法\n");
        return ERROR;
    }
    if(num_w<0||num_w>=(*G)->vexnum) {
        printf("      访问越界，顶点的位序num_w非法\n");
        return ERROR;
    }

    //删除边
    int i;//计数器
    ArcNode *temp=NULL;//用于遍历邻接边
    ArcNode *temp_del=NULL;//用于存放待删除结点

    //删除v->w
    if((*G)->vertices[num_v].firstarc){//若有邻接点
        temp=(*G)->vertices[num_v].firstarc;
        if(temp->adjvex==num_w){//若首邻接点为num
            (*G)->vertices[num_v].firstarc=temp->nextarc;
            free(temp);
        }
        else{//否则遍历邻接边
            for(;temp->nextarc!=NULL;temp=temp->nextarc){//遍历邻接边
                if(temp->nextarc->adjvex==num_w && temp->nextarc->nextarc!=NULL){//若temp->next邻接num且不为末邻接点
                    temp_del=temp->nextarc;
                    temp->nextarc=temp->nextarc->nextarc;
                    free(temp_del);
                    break;
                }
                if(temp->nextarc->adjvex==num_w && temp->nextarc->nextarc==NULL){//若temp->next邻接num且为末邻接点
                    free(temp->nextarc);
                    temp->nextarc=NULL;
                    break;
                }
            }
        }
    }
    //删除w->v
    if((*G)->vertices[num_w].firstarc){//若有邻接点
        temp=(*G)->vertices[num_w].firstarc;
        if(temp->adjvex==num_v){//若首邻接点为num
            (*G)->vertices[num_w].firstarc=temp->nextarc;
            free(temp);
            (*G)->arcnum--;
            return OK;
        }
        else{//否则遍历邻接边
            for(;temp->nextarc!=NULL;temp=temp->nextarc){//遍历邻接边
                if(temp->nextarc->adjvex==num_v && temp->nextarc->nextarc!=NULL){//若temp->next邻接num且不为末邻接点
                    temp_del=temp->nextarc;
                    temp->nextarc=temp->nextarc->nextarc;
                    free(temp_del);
                    (*G)->arcnum--;
                    return OK;
                }
                if(temp->nextarc->adjvex==num_v && temp->nextarc->nextarc==NULL){//若temp->next邻接num且为末邻接点
                    free(temp->nextarc);
                    temp->nextarc=NULL;
                    (*G)->arcnum--;
                    return OK;
                }
            }
        }
    }

    //若删除失败
    printf("      顶点v与w之间无邻接边\n");
    return ERROR;
}

/**
 * DFSTraverse的子函数
 **/
void DFS(ALGraph G, int i, int *visited)
{
    //深度优先搜索遍历图的递归实现
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
 * 函数名称：DFSTraverse
 * 函数参数：图G
 * 函数功能：深度优先遍历图
 * 返回值：成功遍历则返回OK，否则返回ERROR
 **/
status DFSTraverse(ALGraph G)
{
    //深度优先搜索遍历图
    int i;                             //计数器
    int visited[MAX_VERTEX_NUM];       //顶点访问标记

    for (i = 0; i < G->vexnum; i++){//初始化访问标记
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
 * 函数名称：BFSTraverse
 * 函数参数：图G
 * 函数功能：广度优先遍历图
 * 返回值：成功遍历则返回OK，否则返回ERROR
 **/
status BFSTraverse(ALGraph G)
{
    //广度优先搜索遍历
    int head = 0;
    int rear = 0;
    int queue[MAX_VERTEX_NUM];     //辅组队列
    int visited[MAX_VERTEX_NUM];   //顶点访问标记
    int i, j, k;        //计数器
    ArcNode *temp=NULL;

    for (i = 0; i < G->vexnum; i++){//初始化访问标记
        visited[i] = 0;
    }

    printf("      BFS: ");
    for (i = 0; i < G->vexnum; i++){
        if (!visited[i]){
            visited[i] = 1;
            printf("%c ", G->vertices[i].data);
            queue[rear++] = i;  //头结点入队列
        }
        while (head != rear) {
            j = queue[head++];  //出队列
            temp = G->vertices[j].firstarc;
            while (temp != NULL){
                k = temp->adjvex;
                if (!visited[k]){
                    visited[k] = 1;
                    printf("%c ", G->vertices[k].data);
                    queue[rear++] = k; //未访问的周边结点入队列
                }
                temp = temp->nextarc;
            }
        }
    }
    printf("\n");

    return OK;
}

/**
 * 函数名称：LoadList
 * 函数参数：图G的地址，文件名filename
 * 函数功能：数据加载，将文件中数据读入，覆盖当前图
 * 返回值：加载成功返回OK，加载失败返回ERROR
 **/
status LoadFile(ALGraph *G,char *filename)
{
    ALGraph G_temp=NULL;
    char Vertex[MAX];//顶点集缓冲区
    Relation *VR;//边关系缓冲区
    Vertex[0]='\0';//初始化
    VR=(Relation*)malloc(sizeof(Relation));
    VR->next=NULL;//初始化
    FILE *fp;//文件指针
    fp = fopen(filename, "r");
    if(fp==NULL) {
        printf("文件不存在！\n");
        return ERROR;
    }

    //将文件中数据读入系统
    fscanf(fp,"%s\r\n",Vertex);//读取vertex
    //构建VR
    char tail,head;
    int weight;
    Relation *temp=VR;//用于遍历
    Relation *insert=NULL;//待插入结点
    while(fscanf(fp,"%c %c %d\r\n",&tail,&head,&weight)!=EOF){
        //新结点赋值
        insert=(Relation*)malloc(sizeof(Relation));
        insert->tail=tail;
        insert->head=head;
        insert->weight=weight;
        insert->next=NULL;
        //链接
        temp->next=insert;
        temp=temp->next;
    }

    printf("        尝试建立图：\n");
    if(CreateGraph(&G_temp,Vertex,VR->next)==OK){//若文件内数据能够建图覆盖当前图
        printf("        文件中数据符合要求，覆盖当前图：\n");
        DestroyGraph(G);
        CreateGraph(G,Vertex,VR->next);
        fclose(fp);
        return OK;
    }
    else{
        printf("      文件中数据格式有误，读取失败！\n");
    }
    fclose(fp);
    return ERROR;
}

/**
 * 函数名称：SaveAsFile
 * 函数参数：图G的地址，文件名filename
 * 函数功能：数据保存，将图中数据保存至文件
 * 返回值：保存成功返回OK，加载失败返回ERROR
 **/
status SaveAsFile(ALGraph G,char *filename)
{
    int head = 0;
    int rear = 0;
    int queue[MAX_VERTEX_NUM];     //辅组队列
    int visited[MAX_VERTEX_NUM];   //顶点访问标记
    int i, j, k;        //计数器
    char VR[MAX_VERTEX_NUM];//顶点集
    ArcNode *temp=NULL;
    FILE *fp;
    fp = fopen(filename, "wb+");

    //顶点集存入文件
    for(i=0;i<MAX_VERTEX_NUM;i++){
        VR[i]=G->vertices[i].data;
    }
    fprintf(fp, "%s\r\n", VR);

    //广度遍历将图中元素转换为输入格式并存入文件
    for (i = 0; i < G->vexnum; i++){//初始化访问标记
        visited[i] = 0;
    }
    for (i = 0; i < G->vexnum; i++){
        if (!visited[i]){
            queue[rear++] = i;  //头结点入队列
        }
        while (head != rear) {
            j = queue[head++];  //出队列
            visited[j] = 1;
            temp = G->vertices[j].firstarc;
            while (temp != NULL){
                k = temp->adjvex;
                if (!visited[k]){
                    fprintf(fp,"%c %c %d\r\n",G->vertices[j].data,G->vertices[k].data,temp->info);
                    queue[rear++] = k; //未访问的周边结点入队列
                }
                temp = temp->nextarc;
            }
        }
    }

    fclose(fp);
    return OK;
}

/**
 * 函数名称：MulList
 * 函数参数：图G的地址，多图表头M的地址，当前图序号list_num_cur，欲切换到的图序号list_num
 * 函数功能：切换操作图。
 * 返回值：成功切换返回OK，否则返回ERROR
 **/
status MulList(ALGraph *G,MulNode *M,int list_num_cur,int list_num){
    //切换操作图，若目标图不存在则新建
    MulNode *mul_temp=NULL;//用于遍历多图结构
    MulNode *mul_new=NULL;//用于新建多图结点
    //存储图
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//给多图结构中的对应节点赋值，保存数据
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*G);
            break;
        }
    }

    //切换图（为图头指针G赋值）
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//查询多图结构中的对应节点，切换操作表
        if(mul_temp->next->list_num==list_num){//若查询成功，读入图
            (*G) = mul_temp->next->list_head;
            return OK;
        }
    }
    //若查询失败，在多图结构中新建图，此时mul_temp->next指针已经指向链表尾部NULL
    mul_new = (MulNode *)malloc(sizeof(MulNode));
    if (mul_new==NULL) return OVERFLOW;   //分配空间失败

    mul_new -> list_num = list_num;//赋值表序
    mul_new -> list_head = NULL;//新表头节点置空
    mul_new -> next = NULL;//新节点next置空

    mul_temp -> next = mul_new;//为新节点赋值
    M->list_num++;//记录多表个数+1

    (*G) = mul_new -> list_head;

    return ERROR;
}
