#include "LinearTable.h"

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

    LinkList L=NULL;//当前表表头

    int list_num=1;//表序号
    int list_num_cur=0;//记录当前表序号
    int op=1;
    int i;//位序
    int e;//返回位序i的值e
    int cur;//需要寻找前驱或后继的数据
    int pre_e;//返回前驱
    int next_e;//返回后继
    int flag;//多表操作中记录函数返回值
    char filename[20];

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Chain Structure \n");
        printf("      当前操作的表序号为%d\n",list_num);
        printf("-------------------------------------------------\n");
        printf("    	  1. IntiaList       9.  NextElem\n");
        printf("    	  2. DestroyList     10. ListInsert\n");
        printf("    	  3. ClearList       11. ListDelete \n");
        printf("    	  4. ListEmpty       12. ListTrabverse\n");
        printf("    	  5. ListLength      13. OpenFile\n");
        printf("    	  6. GetElem         14. SaveAsFile\n");
        printf("    	  7. LocateElem      15. MulList\n");
        printf("    	  8. PriorElem       \n\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~15]:");
        scanf("%d",&op);

    switch(op){
        case 1:
            //printf("\n----IntiaList功能待实现！\n");
            if(L) printf("      线性表已初始化，初始化失败！\n");
            else{
                if(IntiaList(&L)==OK) printf("      线性表创建成功！\n");
                else printf("      线性表已存在或存储空间不足，创建失败！\n");
            }
            getchar();getchar();
            break;
        case 2:
            //printf("\n----DestroyList功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");
            else{
                if(DestroyList(&L)==OK) printf("      线性表销毁成功！\n");
            }
            getchar();getchar();
            break;
        case 3:
            //printf("\n----ClearList功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");
            else{
                if(ClearList(&L)==OK) printf("      线性表置空成功！\n");
                else printf("      线性表已为空，置空失败！\n");
            }
            getchar();getchar();
            break;
        case 4:
            //printf("\n----ListEmpty功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else if(ListEmpty(L)==OK) printf("      线性表为空！\n");
            else printf("      线性表不为空！\n");
            getchar();getchar();
            break;
        case 5:
            //printf("\n----ListLength功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      线性表长度为%d！\n",ListLength(L));
            }
            getchar();getchar();
            break;
        case 6:
            //printf("\n----GetElem功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      请输入位序，将为您返回该位序数据元素的值\n\n");
                printf("      位序：");
                scanf("%d",&i);
                if(GetElem(L,i,&e)==OK) printf("      线性表中第%d个数据元素的值为%d\n",i,e);
                else printf("      访问越界，该位序不存在！\n");
            }
            getchar();getchar();
            break;
        case 7:
            //printf("\n----LocateElem功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据的位序\n\n");
                printf("      数据元素的值：");
                scanf("%d",&e);
                if(LocateElem(L,e,&i)==OK) printf("      线性表中值为%d的数据元素的位序为%d\n",e,i);
                else printf("      线性表中未查询到该数据元素！\n");
            }
            getchar();getchar();
            break;
        case 8:
            //printf("\n----PriorElem功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据元素的前驱\n\n");
                printf("      数据元素的值：");
                scanf("%d",&cur);
                if(PriorElem(L,cur, &pre_e)==OK) printf("      线性表中值为%d的数据元素的前驱为%d！\n",cur,pre_e);
                else printf("      线性表中未查询到该数据元素或该数据元素无前驱！\n");
            }
            getchar();getchar();
            break;
        case 9:
            //printf("\n----NextElem功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据元素的后继\n\n");
                printf("      数据元素的值：");
                scanf("%d",&cur);
                if(NextElem(L,cur, &next_e)==OK) printf("      线性表中值为%d的数据元素的后继为%d！\n",cur,next_e);
                else printf("      线性表中未查询到该数据元素或该数据元素无后继！\n");
            }
            getchar();getchar();
            break;
        case 10:
            //printf("\n----ListInsert功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      将要插入数据元素，请输入将要插入的数据元素的位序与值\n\n");
                printf("      位序：");
                scanf("%d",&i);
                printf("      值：");
                scanf("%d",&e);
                if(ListInsert(&L,i,e)==OK) printf("      数据元素插入成功！\n");
                else printf("      越界，数据元素插入失败！\n");
            }
            getchar();getchar();
            break;
        case 11:
            //printf("\n----ListDelete功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                printf("      将要删除数据元素，请输入将要删除的数据元素的位序\n\n");
                printf("      位序：");
                scanf("%d",&i);
                if(ListDelete(&L,i,&e)==OK) printf("      数据元素删除成功，删除的元素为%d！\n",e);
                else printf("      越界，数据元素删除失败！\n");
            }
            getchar();getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse功能待实现！\n");
            if(!L) printf("      线性表未初始化！\n");//表不存在
            else{
                ListTrabverse(L);
                if(!L->next) printf("      线性表是空表！\n");
            }
            getchar();getchar();
            break;
        case 13:
            //printf("\n----读取文件功能待实现！\n");
            if(!L){
                printf("      线性表未初始化！\n");//表不存在
                getchar();
            }
            else{
                printf("      将从文件中读取数据并插入当前线性表表首.\n      请输入要读取的文件名: ");getchar();
                gets(filename);
                if(LoadFile(L,filename)==OK) printf("      文件读取成功，表长为%d.\n",ListLength(L));
                else printf("      文件读取失败，文件不存在或其中无数据\n");
            }
            getchar();
            break;
        case 14:
            //printf("\n----输出文件功能待实现！\n");
            if(!L){
                printf("      线性表未初始化！\n");//表不存在
                getchar();
            }
            else{
                printf("      将线性表中数据保存(写)为文件\n      请输入要写入的文件名: ");getchar();
                gets(filename);
                if(SaveAsFile(L,filename)==OK) printf("      文件写入成功.\n");
            }
            getchar();
            break;
        case 15:
            //printf("\n----多表处理功能待实现！\n");
            list_num_cur=list_num;//记录当前表序以存储数据
            printf("      请输入要切换到的表序号：");
            scanf("%d",&list_num);

            flag=MulList(&L,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      切换成功，当前操作表为表%d\n",list_num);
            else if(flag==ERROR) printf("      表%d不存在，已为您新建表%d并切换(未初始化)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//新表创建失败
                printf("      空间不足，线性表创建失败！\n");
                list_num=list_num_cur;//当前表序回退至换表前
            }

            //输出所有表序
            printf("\n------------------- all list --------------------\n");
            printf("      当前共有%d个线性表可供操作\n      其表序为(依创建时间排序)：\n      ",MulList_head->list_num);
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
 * 函数名称：InitiaList
 * 函数参数：线性表L的地址
 * 函数功能：构造一个空的线性表
 * 返回值：成功构造返回OK，否则返回ERROR
 **/
status IntiaList(LinkList *L){
    //构造一个空线性表
	*L = (LinkList)malloc(sizeof (LNode));
    if(!(*L)) return ERROR;      //存储分配失败
    (*L) -> next = NULL;           //next指针指空-线性表置空
	return OK;
}

/**
 * 函数名称：DestroyList
 * 函数参数：线性表L的地址
 * 函数功能：删除线性表
 * 返回值：成功销毁返回OK，否则返回ERROR
 **/
status DestroyList(LinkList *L){
    //销毁线性表
    LinkList temp;
    LinkList tail;
    for(tail=*L;tail->next!=NULL;){//释放结点空间
        temp=tail;
        tail=tail->next;
        free(temp);
    }
    free(tail);
    (*L)=NULL;
    return OK;
}

/**
 * 函数名称：ClearList
 * 函数参数：线性表L的地址
 * 函数功能：重置线性表
 * 返回值：成功置空返回OK，否则返回ERROR
 **/
status ClearList(LinkList *L){
    //将L重置为空表
    if((*L)->next==NULL) return ERROR;//线性表已为空
    LinkList temp;
    LinkList tail;
    for(tail=(*L)->next;tail->next!=NULL;){//释放数据结点空间
        temp=tail;
        tail=tail->next;
        free(temp);
    }
    free(tail);
    (*L)->next=NULL;//重置为空表
    return OK;
}

/**
 * 函数名称：ListEmpty
 * 函数参数：线性表L
 * 函数功能：判断线性表是否为空
 * 返回值：若L为空表则返回OK，否则返回ERROR
 **/
status ListEmpty(LinkList L){
    //判断L是否为空表，是则返回OK，否则返回ERROR
    if(!L->next) return OK;
    return ERROR;
}

/**
 * 函数名称：ListLength
 * 函数参数：线性表L的
 * 函数功能：计算线性表L中数据元素个数；
 * 返回值：成功返回L中数据元素个数，失败返回ERROR
 **/
int ListLength(LinkList L){
    //计算顺序线性表长度
    int length;
    for(length=0;L->next!=NULL;L=L->next){
        length++;
    }
    return length;
}

/**
 * 函数名称：GetElem
 * 函数参数：线性表L，第i个数据，e为第i个数据；
 * 函数功能：查找并用e返回L中第i个元素的值；
 * 返回值：成功则返回OK，否则返回ERROR
 **/
status GetElem(LinkList L,int i,ElemType *e){
    //用e返回L中第i个数据元素的值
    if(i<1 || i>ListLength(L)) return ERROR;//越界
    for(;i>0;i--){
        L=L->next;
    }
    (*e)=L->data;
    return OK;
}

/**
 * 函数名称：LocateElem
 * 函数参数：线性表L，第i个数据，e为第i个数据；
 * 函数功能：查找L中与e相同数据所在的位序；用i返回该位序
 * 返回值：成功则返回OK，不存在则返回ERROR
 **/
status LocateElem(LinkList L,ElemType e,ElemType *i){//简化过
    //线性表L已存在，用i返回L中第一个e的位序。若这样的e不存在，返回ERROR
    int temp;
    int length = ListLength(L);//直接使用L遍历，故LISTLENGTH的值会变化，使用length存储线性表长度

    for(temp=0;temp<length;temp++){
        L=L->next;
        if(L->data==e){
            (*i)=temp+1;
            return OK;
        }
    }

    return ERROR;//未找到
}

/**
 * 函数名称：PriorElem
 * 函数参数：线性表L，查找的数据cur,前驱pre_e；
 * 函数功能：查找L中与cur相同的第一个数据，并用pre_e返回其前驱
 * 返回值：成功则返回OK；若无前驱以及其他情况则返回ERROR
 **/
status PriorElem(LinkList L,ElemType cur,ElemType *pre_e){
    //若cur是L的数据元素且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre.e无定义
    int cur_e;//cur元素的位序

    if(LocateElem(L,cur,&cur_e)==OK){//若元素存在
        if(cur_e!=1){//不是第一个元素
            GetElem(L,cur_e-1,pre_e);//用pre_e返回前驱元素
            return OK;
        }
    }

    return ERROR;//元素不存在或其无前驱
}

/**
 * 函数名称：NextElem
 * 函数参数：线性表L，查找的数据cur,后继next_e；
 * 函数功能：查找L中与cur相同的第一个数据，并用next_e返回其后继
 * 返回值：成功则返回OK；若无后继以及其他情况则返回ERROR
 **/
status NextElem(LinkList L,ElemType cur,ElemType *next_e){
    //若cur是L的数据元素且不是最后一个，则用next_e返回它的后继，否则操作失败，next.e无定义
    int cur_e;//cur元素的位序

    if(LocateElem(L,cur,&cur_e)==OK){//若元素存在
        if(cur_e!=ListLength(L)){//不是最后一个元素
            GetElem(L,cur_e+1,next_e);//用next_e返回后继元素
            return OK;
        }
    }

    return ERROR;
}

/**
 * 函数名称：ListInsert
 * 函数参数：线性表L的地址，插入的位置i，插入的数据元素e。
 * 函数功能：在L的第i个位置之前插入新的数据元素e；若已插满，则按照分配增量，分配更大的空间。
 * 返回值：成功插入返回OK，否则返回ERROR
 **/
status ListInsert(LinkList *L,int i,ElemType e){
    //在顺序线性表L中第i个位置之前插入新的元素e
    //i的合法值为1≤i≤ListLength+1
    int j;//计数器
    LinkList temp_L=NULL;//临时指针，用于指向第i-1个元素
    LinkList temp_Insert=NULL;//待插入的结点
    if (i<1 || i>ListLength(*L)+1) return ERROR;     //i不合法

    for(temp_L=(*L),j=0;j<i-1;j++){//找到第i-1个结点
        temp_L=temp_L->next;
    }
    temp_Insert = (LinkList)malloc(sizeof(LNode));
    if (temp_Insert==NULL) return OVERFLOW;   //分配空间失败

    temp_Insert -> data = e;
    temp_Insert -> next = temp_L -> next;
    temp_L -> next = temp_Insert;

    return OK;
}

/**
 * 函数名称：ListDelete
 * 函数参数：线性表L的地址，删除的位序i，指针e的地址。
 * 函数功能：删除L的第i个数据元素，用e返回其值。
 * 返回值：成功删除返回OK，否则返回ERROR
 **/
status ListDelete(LinkList *L,int i,ElemType *e)
{
    //删除L的第i个数据元素，用e返回其值
    int j;//计数器

    LinkList temp_L=NULL;//临时指针，用于指向第i-1个元素
    LinkList temp_Delete=NULL;//临时指针，用于指向待删除元素
    if (i<1 || i>ListLength(*L)) return ERROR;     //i不合法

    for(temp_L=(*L),j=0;j<i-1;j++){//找到第i-1个结点
        temp_L=temp_L->next;
    }
    temp_Delete = temp_L->next;
    (*e)=temp_Delete->data;

    if (temp_L -> next -> next){//如果被删除元素不是最后一个
        temp_L -> next = temp_L -> next -> next;
    }
    else temp_L -> next = NULL;//被删除元素是最后一个，则前一个结点指空
    free(temp_Delete);
    return OK;
}

/**
 * 函数名称：ListTrabverse
 * 函数参数：线性表L
 * 函数功能：依次显示线性表中的每个元素。
 * 返回值：成功遍历返回线性表的长度，否则返回ERROR
 **/
status ListTrabverse(LinkList L){
    int i;//计数器
    printf("\n----------------- all elements ------------------\n");
    for(i=0;i<ListLength(L);) {
        L=L->next;
        printf("%d ",L->data);
    }
    printf("\n---------------------- end ----------------------\n");
    return OK;
}

/**
 * 函数名称：LoadFile
 * 函数参数：线性表L，文件名filename
 * 函数功能：将文件中数据读入，插入当前线性表。
 * 返回值：成功读取返回OK，否则返回ERROR
 **/
status LoadFile(LinkList L,char filename[20]){
    ElemType elem_read;//读取文件缓存
    int i=0;//计数器
    FILE *fp;
    fp = fopen(filename, "r");
    /*将文件中十进制字符形式元素依次按读入系统*/
    while(fscanf(fp,"%d ",&elem_read)!=EOF){
        printf("      读入第%d个元素:%d...\n", ++i , elem_read);
        ListInsert(&L,i,elem_read);//插入读到的数据
    }
    fclose(fp);

    if(!i) return ERROR;
    else return OK;
}

/**
 * 函数名称：SaveAsFile
 * 函数参数：线性表L，文件名filename
 * 函数功能：将线性表中数据存入文件。
 * 返回值：若成功写入则返回OK，否则返回ERROR
 **/
status SaveAsFile(LinkList L,char filename[20]){
    ElemType elem_read;//读取文件缓存
    int i;//计数器
    FILE *fp;
    fp = fopen(filename, "wb+");
    /*将表中元素依次按十进制字符形式写入文件*/
    LinkList temp_L=L;
    for (i = 1; i <= ListLength(L); i++){
        temp_L = temp_L->next;
        printf("      写入第%d个元素:%d...\n", i , temp_L->data);
        fprintf(fp, "%d ", temp_L->data);
    }
    fclose(fp);
    return OK;
}

/**
 * 函数名称：MulList
 * 函数参数：线性表L的地址，多表表头M的地址，当前表序号list_num_cur，欲切换到的表序号list_num
 * 函数功能：切换操作表。
 * 返回值：成功切换返回OK，否则返回ERROR
 **/
status MulList(LinkList *L,MulNode *M,int list_num_cur,int list_num){
    //切换操作表，若目标表不存在则新建
    MulNode *mul_temp=NULL;//用于遍历多表结构
    MulNode *mul_new=NULL;//用于新建多表结点
    //存储表
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//给多表结构中的对应节点赋值，保存数据
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*L);
            break;
        }
    }

    //切换表（为表头L赋值）
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//查询多表结构中的对应节点，切换操作表
        if(mul_temp->next->list_num==list_num){//若查询成功，读入表
            (*L) = mul_temp->next->list_head;
            return OK;
        }
    }
    //若查询失败，在多表结构中新建表，此时mul_temp->next指针已经指向链表尾部NULL
    mul_new = (MulNode *)malloc(sizeof(MulNode));
    if (mul_new==NULL) return OVERFLOW;   //分配空间失败

    mul_new -> list_num = list_num;//赋值表序
    mul_new -> list_head = NULL;//新表头节点置空
    mul_new -> next = NULL;//新节点next置空

    mul_temp -> next = mul_new;//为新节点赋值
    M->list_num++;//记录多表个数+1

    (*L) = mul_new -> list_head;

    return ERROR;
}
