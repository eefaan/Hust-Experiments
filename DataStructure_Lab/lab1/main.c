#include "LinearTable.h"

void main(void){
    SqList MulList[MAX];//多表
    int temp;
    for(temp=0;temp<MAX;temp++){//初始化elem为null
        MulList[temp].elem=NULL;
    }
    SqList *L;//当前表
    int list_num=0;
    L=MulList+list_num;//指向表1

    int op=1;
    int length;//线性表长度
    int i;//位序
    int e;//返回位序i的值e
    int cur;//需要寻找前驱或后继的数据
    int pre_e;//返回前驱
    int next_e;//返回后继
    ElemType elem_read;//读取文件缓存
    FILE *fp;
    char filename[20];

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("      当前操作的表序号为%d\n",list_num+1);
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
            if(IntiaList(L)==OK) printf("      线性表创建成功！\n");
            else printf("      线性表已存在或存储空间不足，创建失败！\n");
            getchar();getchar();
            break;
        case 2:
            //printf("\n----DestroyList功能待实现！\n");
            if(DestroyList(L)==OK) printf("      线性表销毁成功！\n");
            else printf("      线性表不存在，销毁失败！\n");
            getchar();getchar();
            break;
        case 3:
            //printf("\n----ClearList功能待实现！\n");
            if(ClearList(L)==OK) printf("      线性表置空成功！\n");
            else printf("      线性表不存在或线性表已为空，置空失败！\n");
            getchar();getchar();
            break;
        case 4:
            //printf("\n----ListEmpty功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else if(ListEmpty(*L)==OK) printf("      线性表为空！\n");
            else printf("      线性表不为空！\n");
            getchar();getchar();
            break;
        case 5:
            //printf("\n----ListLength功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                length=ListLength(L);
                printf("      线性表长度为%d！\n",length);
            }
            getchar();getchar();
            break;
        case 6:
            //printf("\n----GetElem功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      请输入位序，将为您返回该位序数据元素的值\n\n");
                printf("      位序：");
                scanf("%d",&i);
                if(GetElem(*L,i,&e)==OK) printf("      线性表中第%d个数据元素的值为%d\n",i,e);
                else printf("      访问越界，该位序不存在！\n");
            }
            getchar();getchar();
            break;
        case 7:
            //printf("\n----LocateElem功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据的位序\n\n");
                printf("      数据元素的值：");
                scanf("%d",&e);
                if(LocateElem(*L,e,&i)==OK) printf("      线性表中值为%d的数据元素的位序为%d\n",e,i);
                else printf("      线性表中未查询到该数据元素！\n");
            }
            getchar();getchar();
            break;
        case 8:
            //printf("\n----PriorElem功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据元素的前驱\n\n");
                printf("      数据元素的值：");
                scanf("%d",&cur);
                if(PriorElem(*L,cur, &pre_e)==OK) printf("      线性表中值为%d的数据元素的前驱为%d！\n",cur,pre_e);
                else printf("      线性表中未查询到该数据元素或该数据元素无前驱！\n");
            }
            getchar();getchar();
            break;
        case 9:
            //printf("\n----NextElem功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      请输入数据元素的值，将为您返回该数据元素的后继\n\n");
                printf("      数据元素的值：");
                scanf("%d",&cur);
                if(NextElem(*L,cur, &next_e)==OK) printf("      线性表中值为%d的数据元素的后继为%d！\n",cur,next_e);
                else printf("      线性表中未查询到该数据元素或该数据元素无后继！\n");
            }
            getchar();getchar();
            break;
        case 10:
            //printf("\n----ListInsert功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      将要插入数据元素，请输入将要插入的数据元素的位序与值\n\n");
                printf("      位序：");
                scanf("%d",&i);
                printf("      值：");
                scanf("%d",&e);
                if(ListInsert(L,i,e)==OK) printf("      数据元素插入成功！\n");
                else printf("      越界，数据元素插入失败！\n");
            }
            getchar();getchar();
            break;
        case 11:
            //printf("\n----ListDelete功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else{
                printf("      将要删除数据元素，请输入将要删除的数据元素的位序\n\n");
                printf("      位序：");
                scanf("%d",&i);
                if(ListDelete(L,i,&e)==OK) printf("      数据元素删除成功，删除的元素为%d！\n",e);
                else printf("      越界，数据元素删除失败！\n");
            }
            getchar();getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse功能待实现！\n");
            if(!L->elem) printf("      线性表未创建！\n");//表不存在
            else if(!ListTrabverse(*L)) printf("      线性表是空表！\n");
            getchar();getchar();
            break;
        case 13:
            //printf("\n----读取文件功能待实现！\n");
            if(!L->elem){
                printf("      线性表未创建！\n");//表不存在
                getchar();getchar();
            }
            else{
                printf("      将从文件中读取数据并插入当前线性表表首.\n      请输入要读取的文件名: ");
                getchar();
                gets(filename);
                fp = fopen(filename, "r");
                i=0;
                /*将文件中十进制字符形式元素依次按读入系统*/
                while(fscanf(fp,"%d ",&elem_read)!=EOF){
                    printf("      读入第%d个元素:%d...\n", ++i , elem_read);
                    ListInsert(L,i,elem_read);//插入读到的数据
                }
                if(!i) printf("      文件读取失败，文件不存在或其中无数据\n");
                else printf("      文件读取成功，表长为%d.\n",L->length);
                fclose(fp);getchar();
            }
            break;
        case 14:
            //printf("\n----输出文件功能待实现！\n");
            if(!L->elem){
                printf("      线性表未创建！\n");//表不存在
                getchar();getchar();
            }
            else{
                printf("      请输入要写入的文件名: ");
                getchar();
                gets(filename);
                fp = fopen(filename, "wb+");
                /*将表中元素依次按十进制字符形式写入文件*/
                for (i = 1; i <= L->length; i++){
                    printf("      写入第%d个元素:%d...\n", i , L->elem[i]);
                    fprintf(fp, "%d ", L->elem[i]);
                }
                printf("      文件写入成功.\n");
                fclose(fp);getchar();
            }
            break;
        case 15:
            //printf("\n----多表处理功能待实现！\n");
            printf("      请输入要切换到的表序号[1~%d]：",MAX);
            scanf("%d",&list_num);
            if(--list_num<0 || list_num>MAX-1){
                printf("\n      对应表不存在，切换为表1\n");
                list_num=0;
                getchar();getchar();
                break;
            }
            else printf("\n      多表操作切换成功！\n");
            L=MulList+list_num;
            getchar();getchar();
            break;
        case 0:
            break;
        }//end of switch

    }//end of while

    printf("\n    欢迎下次再使用本系统！\n");
}//end of main()

/**
 * 函数名称：InitiaList
 * 函数参数：线性表L的地址
 * 函数功能：构造一个空的线性表
 * 返回值：成功构造返回OK，否则返回ERROR
 **/
status IntiaList(SqList *L){
    //构造一个空链表
    if(L->elem) return ERROR;       //表已被初始化
	L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) return ERROR;      //存储分配失败
	L->length=0;                    //空表长度为0
    L->listsize=LIST_INIT_SIZE;     //初始存储容量
	return OK;
}

/**
 * 函数名称：DestroyList
 * 函数参数：线性表L的地址
 * 函数功能：删除线性表
 * 返回值：成功销毁返回OK，否则返回ERROR
 **/
status DestroyList(SqList *L){
    //销毁线性表
    if(!L->elem) return ERROR;//表不存在
    free(L->elem);
    L->elem=NULL;
    return OK;
}

/**
 * 函数名称：ClearList
 * 函数参数：线性表L的地址
 * 函数功能：重置线性表
 * 返回值：成功置空返回OK，否则返回ERROR
 **/
status ClearList(SqList *L){
    //将L重置为空表
    if(!L->elem) return ERROR;//表不存在
    if(L->length==0) return ERROR;//线性表已为空
    L->elem=NULL;
    IntiaList(L);
    return OK;
}

/**
 * 函数名称：ListEmpty
 * 函数参数：线性表L
 * 函数功能：判断线性表是否为空
 * 返回值：若L为空表则返回OK，否则返回ERROR
 **/
status ListEmpty(SqList L){
    //判断L是否为空表，是则返回OK，否则返回ERROR
    if(L.length == 0) return OK;
    else return ERROR;
}

/**
 * 函数名称：ListLength
 * 函数参数：线性表L的地址
 * 函数功能：计算线性表L中数据元素个数；
 * 返回值：成功返回L中数据元素个数，失败返回ERROR
 **/
int ListLength(SqList *L){
    //计算顺序线性表长度
    if(L) return L->length;
    return ERROR;
}

/**
 * 函数名称：GetElem
 * 函数参数：线性表L，第i个数据，e为第i个数据；
 * 函数功能：查找并用e返回L中第i个元素的值；
 * 返回值：成功则返回OK，否则返回ERROR
 **/
status GetElem(SqList L,int i,ElemType *e){
    //用e返回L中第i个数据元素的值
    if(i<1 || i>L.length) return ERROR;//越界
    else (*e)=L.elem[i];
    return OK;
}

/**
 * 函数名称：LocateElem
 * 函数参数：线性表L，第i个数据，e为第i个数据；
 * 函数功能：查找L中与e相同数据所在的位序；用i返回该位序
 * 返回值：成功则返回OK，不存在则返回ERROR
 **/
status LocateElem(SqList L,ElemType e,ElemType *i){//简化过
    //线性表L已存在，用i返回L中第一个e的位序。若这样的e不存在，返回ERROR
    int temp;

    for(temp=1;temp<=L.length;temp++){
        if(L.elem[temp]==e){
            (*i)=temp;
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
status PriorElem(SqList L,ElemType cur,ElemType *pre_e){
    //若线性表L已存在
    //若cur是L的数据元素且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre.e无定义
    int cur_e;//位序

    if(LocateElem(L,cur,&cur_e)==OK){
        if(cur_e!=1){
            (*pre_e) = L.elem[cur_e-1];
            return OK;
        }
    }

    return ERROR;
}

/**
 * 函数名称：NextElem
 * 函数参数：线性表L，查找的数据cur,后继next_e；
 * 函数功能：查找L中与cur相同的第一个数据，并用next_e返回其后继
 * 返回值：成功则返回OK；若无后继以及其他情况则返回ERROR
 **/
status NextElem(SqList L,ElemType cur,ElemType *next_e){
    //若线性表L已存在
    //若cur是L的数据元素且不是最后一个，则用next_e返回它的后继，否则操作失败，next.e无定义
    int cur_e;//位序

    if(LocateElem(L,cur,&cur_e)){
        if(cur_e!=L.length){
            (*next_e) = L.elem[cur_e+1];
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
status ListInsert(SqList *L,int i,ElemType e){
    //在顺序线性表L中第i个位置之前插入新的元素e
    int j;
    //i的合法值为1≤i≤ListLength+1
    if (i<1 || i>L->length+1) return ERROR;     //i不合法
    if (L->length >= L->listsize){    //溢出，扩充存储空间
        ElemType *newbase = (ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if (newbase==NULL) return OVERFLOW;   //分配空间失败
        L->elem = newbase;
        L->listsize += LISTINCREMENT; // 增加固定大小存储容量
	 }
    //向后移动元素，空出第i个元素的分量elem[i-1]
    for(j=L->length;j>=i;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i]=e;      /*新元素插入*/  //j+1
    L->length++;         /*线性表长度加1*/
    return OK;
}

/**
 * 函数名称：ListDelete
 * 函数参数：线性表L的地址，删除的位序i，指针e的地址。
 * 函数功能：删除L的第i个数据元素，用e返回其值。
 * 返回值：成功删除返回OK，否则返回ERROR
 **/
status ListDelete(SqList *L,int i,ElemType *e)
{
    //删除L的第i个数据元素，用e返回其值
    int j;

    if (i<1 || i>L->length) return ERROR;
    else {
        (*e)=L->elem[i];
        for(j=i;j<L->length;j++)
            L->elem[j]=L->elem[j+1];
        L->length--;
    }

    return OK;
}

/**
 * 函数名称：ListTrabverse
 * 函数参数：线性表L
 * 函数功能：依次显示线性表中的每个元素。
 * 返回值：成功遍历返回线性表的长度，否则返回ERROR
 **/
status ListTrabverse(SqList L){
   int i;
   printf("\n----------------- all elements ------------------\n");
   for(i=1;i<=L.length;i++) printf("%d ",L.elem[i]);
   printf("\n---------------------- end ----------------------\n");
   return L.length;
}
