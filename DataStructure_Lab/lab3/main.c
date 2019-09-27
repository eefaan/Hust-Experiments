#include"bitree.h"

int key_static[MAX];//生成所有结点的key
int list_num=1;//树序号（名字）

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

    int list_num_cur=0;//记录当前表序号
    int flag;//多表操作中记录函数返回值

    BiTree T=NULL;//当前二叉树头指针 lchild指向根节点
    BiTree temp=NULL;//用于暂时存放查询到的结点
    ElemType elem;//用于传递数据元素值
    int key;//用于传递key值
    int LR;//用于选择对左右子树进行操作
    char definition[MAX];//用于creat树
    char filename[MAX];

    int op=1;

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Binary Tree On Chain Structure \n");
        printf("      当前操作的树序号为%d\n",list_num);
        printf("-------------------------------------------------\n");
        printf("    	  1.  IntiaBitree         2.  DestroyBiTree\n");
        printf("    	  3.  CreatBiTree         4.  ClearBiTree\n");
        printf("    	  5.  BiTreeEmpty         6.  BiTreeDepth\n");
        printf("    	  7.  Root                8.  Value\n");
        printf("    	  9.  Assign\n");
        printf("-------------------------------------------------\n");
        printf("    	  10. Parent              11. LeftChild\n");
        printf("    	  12. RightChild          13. LeftSibling\n");
        printf("    	  14. RightSibling\n");
        printf("-------------------------------------------------\n");
        printf("    	  15. InsertChild         16. DeleteChild\n");
        printf("    	  17. PreOrderTraverse    18. InOrderTraverse\n");
        printf("    	  19. PostOrderTraverse   20. LevelOrderTraverse\n");
        printf("-------------------------------------------------\n");
        printf("    	  21. LoadFile            22. SaveAsFile\n");
        printf("    	  23. MulTree       \n");
        printf("-------------------------------------------------\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~23]:");
        scanf("%d",&op);

    switch(op){
        case 1:
            //初始化
            if(T) printf("      二叉树已初始化，初始化失败！\n");
            else{
                if(InitBiTree(&T)==OK) printf("      二叉树初始化成功！\n");
                else printf("      存储空间不足，初始化失败！\n");
            }
            getchar();getchar();
            break;
        case 2:
            //销毁
            if(!T) printf("      二叉树未初始化！\n");
            else{
                if(DestroyBiTree(&T)==OK) printf("      二叉树销毁成功！\n");
                key_static[list_num]=0;//key重新生成
            }
            getchar();getchar();
            break;
        case 3:
            //创建
            if(!T) printf("      二叉树未初始化！\n");
            else{
                printf("      请输入字符串definition以先序方式新建二叉树\n      输入样例：abc   de  f  (无需输入key值，将自动生成，欲查询结点对应key值可遍历二叉树)\n      (其中空格代表该处为空结点)：");
                definition[0]='\0';
                getchar();
                scanf("%[^\n]",definition);
                if(definition[0]=='\0'){
                    printf("      输入definition序列不能为空！\n");
                }
                else if(CreatBiTree(&T,&definition)==OK) printf("      二叉树创建成功！\n");
                else printf("      创建失败，字符串内元素未全部使用，请检查定义是否符合规则！\n");
            }
            getchar();getchar();
            break;
        case 4:
            //清空
            if(!T) printf("      二叉树未初始化！\n");
            else{
                if(ClearBiTree(&T)==OK) printf("      二叉树置空成功！\n");
                else printf("      二叉树已为空，置空失败！\n");
                key_static[list_num]=0;//key重新生成
            }
            getchar();getchar();
            break;
        case 5:
            //判断是否为空
            if(!T) printf("      二叉树未初始化！\n");//表不存在
            else if(BiTreeEmpty(T)==OK) printf("      二叉树为空！\n");
            else printf("      二叉树不为空！\n");
            getchar();getchar();
            break;
        case 6:
            //求二叉树最大深度
            if(!T) printf("      二叉树未初始化！\n");//表不存在
            else{
                printf("      二叉树最大深度为%d！\n",BiTreeDepth(T));
            }
            getchar();getchar();
            break;
        case 7:
            //根的值
            if(!T) printf("      二叉树未初始化！\n");//表不存在
            else{
                if(Root(T,&key,&elem)==OK) printf("      二叉树的根key为%d,数据为%c",key,elem);
                else printf("      该二叉树为空树，无根！\n");
            }
            getchar();getchar();
            break;
        case 8:
            //关键字为key的结点的数据
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点数据\n\n");
                printf("      key：");
                scanf("%d",&key);
                if(Value(T,key,&elem)==OK) printf("      线性表中key为%d的数据元素值为%c\n",key,elem);
                else printf("      不存在key为%d的结点！\n",key);
            }
            getchar();getchar();
            break;
        case 9:
            //给关键字为key的结点赋值
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key与数据elem，将为该结点赋值\n\n");
                printf("      key：");
                scanf("%d",&key);
                getchar();
                printf("      elem：");
                scanf("%c",&elem);
                if(Assign(&T,key,elem)==OK) printf("      线性表中key为%d的数据元素值更改成功\n",key);
                else printf("      不存在key为%d的结点！\n",key);
            }
            getchar();getchar();
            break;
        case 10:
            //查找Parent结点
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点的双亲\n\n");
                printf("      key：");
                scanf("%d",&key);
                temp=Parent(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      线性表中key为%d的结点的双亲结点key为%d，data为%c\n",key,temp->key,temp->data);
                else printf("      不存在key为%d的结点或该结点为根节点无双亲！\n",key);
            }
            temp=NULL;//置空暂存结点
            getchar();getchar();
            break;
        case 11:
            //查找LeftChild结点
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点的左子结点\n\n");
                printf("      key：");
                scanf("%d",&key);
                temp=LeftChild(T->lchild,key);
                if(temp!=NULL) printf("      线性表中key为%d的结点的左孩子结点key为%d，data为%c\n",key,temp->key,temp->data);
                else printf("      不存在key为%d的结点或该结点无左子结点！\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 12:
            //查找RightChild结点
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点的右子结点\n\n");
                printf("      key：");
                scanf("%d",&key);
                temp=RightChild(T->lchild,key);
                if(temp!=NULL) printf("      线性表中key为%d的结点的右孩子结点key为%d，data为%c\n",key,temp->key,temp->data);
                else printf("      不存在key为%d的结点或该结点无右子结点！\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 13:
            //查找LeftSiBling结点
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点的左兄弟结点\n\n");
                printf("      key：");
                scanf("%d",&key);
                temp=LeftSibling(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      线性表中key为%d的结点的左兄弟结点key为%d，data为%c\n",key,temp->key,temp->data);
                else printf("      不存在key为%d的结点或该结点无左兄弟结点！\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 14:
            //查找RightSiBling结点
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key，将为您返回该结点的右兄弟结点\n\n");
                printf("      key：");
                scanf("%d",&key);
                temp=RightSibling(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      线性表中key为%d的结点的右兄弟结点key为%d，data为%c\n",key,temp->key,temp->data);
                else printf("      不存在key为%d的结点或该结点无右兄弟结点！\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 15:
            //插入子树
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key与选项LR，将为您插入在key结点处子树\n      （LR=0：插入至左子树；LR=1：插入至右子树）\n\n");
                printf("      key：");
                scanf("%d",&key);
                getchar();
                printf("      LR：");
                scanf("%d",&LR);
                if(LR!=0&&LR!=1) printf("      输入LR有误，返回主菜单！\n");
                else if(InsertChild(&T,key,LR)==OK) printf("      插入成功！\n");
                else printf("      插入失败！\n");
            }
            getchar();getchar();
            break;
        case 16:
            //删除子树
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else{
                printf("      请输入关键字key与选项LR，将为您删除key结点子树\n      （LR=0：删除左子树；LR=1：删除右子树）\n\n");
                printf("      key：");
                scanf("%d",&key);
                getchar();
                printf("      LR：");
                scanf("%d",&LR);
                if(LR!=0&&LR!=1) printf("      输入LR有误，返回主菜单！\n");
                else if(DeleteChild(&T,key,LR)==OK) printf("      删除成功！\n");
                else printf("      删除失败！\n");
            }
            getchar();getchar();
            break;
        case 17:
            //先序遍历输出二叉树中数据
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else if(!T->lchild) {//是否为空树
                printf("      二叉树为空！\n");            }
            else{
                printf("      二叉树的先序遍历结果：\n");
                printf("--------------------------------------------\n");
                PreOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 18:
            //中序遍历输出二叉树中数据
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else if(!T->lchild) {//是否为空树
                printf("      二叉树为空！\n");            }
            else{
                printf("      二叉树的中序遍历结果：\n");
                printf("--------------------------------------------\n");
                InOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 19:
            //后序遍历输出二叉树中数据
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else if(!T->lchild) {//是否为空树
                printf("      二叉树为空！\n");            }
            else{
                printf("      二叉树的后序遍历结果：\n");
                printf("--------------------------------------------\n");
                PostOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 20:
            //层次遍历输出二叉树中数据
            if(!T) printf("      二叉树未初始化！\n");//树不存在
            else if(!T->lchild) {//是否为空树
                printf("      二叉树为空！\n");
            }
            else{
                printf("      二叉树的层次遍历结果：\n");
                printf("--------------------------------------------\n");
                LevelOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 21:
            //读取文件
            if(!T){
                printf("      二叉树未初始化！\n");//树不存在
                getchar();
            }
            else{
                printf("      将从文件中读取数据并覆盖当前二叉树.\n      请输入要读取的文件名: ");getchar();
                gets(filename);
                if(LoadFile(&T,filename)==OK) printf("      文件读取成功！\n");
                else printf("      文件读取失败！\n");
            }
            getchar();
            break;
        case 22:
            //存储文件
            if(!T){
                printf("      二叉树未初始化！\n");//树不存在
                getchar();
            }
            else if(!T->lchild){
                printf("      二叉树为空！无法存储\n");
                getchar();
            }
            else{
                printf("      将二叉树中数据保存(写)为文件\n      请输入要写入的文件名: ");getchar();
                gets(filename);
                if(SaveAsFile(T->lchild,filename)==OK) printf("      文件写入成功！\n");
            }
            getchar();
            break;
        case 23:
            list_num_cur=list_num;//记录当前表序以存储数据
            printf("      请输入要切换到的树序号：");
            scanf("%d",&list_num);

            flag=MulList(&T,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      切换成功，当前操作树为树%d\n",list_num);
            else if(flag==ERROR) printf("      树%d不存在，已为您新建树%d并切换(未初始化)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//新树创建失败
                printf("      空间不足，树创建失败！\n");
                list_num=list_num_cur;//当前表序回退至换表前
            }

            //输出所有树序号
            printf("\n------------------- all list --------------------\n");
            printf("      当前共有%d个树可供操作\n      其序号为(依创建时间排序)：\n      ",MulList_head->list_num);
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
 * 函数名称：InitBiTree
 * 函数参数：二叉树T的地址
 * 函数功能：构造一个空的二叉树
 * 返回值：成功构造返回OK，否则返回ERROR
 **/
status InitBiTree(BiTree *T)
{
    //构造一个二叉树
    *T = (BiTree)malloc(sizeof(BiTNode));
    if(!(*T)) return ERROR;      //存储分配失败
    (*T)->lchild=NULL;           //二叉树头结点置空
    (*T)->rchild=NULL;           //右子结点置空
    return OK;
}

/**
 * DestroyBiTree的子函数
 **/
void DestroyF(BiTree *T)
{
    //递归释放结点空间
    if((*T)->lchild) DestroyF(&((*T)->lchild));
    if((*T)->rchild) DestroyF(&((*T)->rchild));
    free(*T);
}
/**
 * 函数名称：DestroyBiTree
 * 函数参数：二叉树T的地址
 * 函数功能：删除二叉树
 * 返回值：成功删除返回OK，否则返回ERROR
 **/
status DestroyBiTree(BiTree *T)
{
    //销毁二叉树
    DestroyF(T);
    (*T)=NULL;
    return OK;
}

/**
 * CreatBiTree的子函数
 **/
void CreatF(BiTree *T,char **d)
{
    //递归赋值
    if (**d ==' ') {
        (*T)=NULL;
        (*d)++;
    }
    else
    {
        (*T)=(BiTree)malloc(sizeof(BiTNode));
        (*T)->key =key_static[list_num]++;
        (*T)->data=*((*d)++);                //生成根结点
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;

        if(**d!='\0')CreatF(&(*T)->lchild,d); //递归构造左子树
        if(**d!='\0')CreatF(&(*T)->rchild,d); //递归构造右子树
    }
}
/**
 * 函数名称：CreatBiTree
 * 函数参数：二叉树T的地址，先序序列definition
 * 函数功能：根据先序序列definition创建二叉树
 * 返回值：成功创建返回OK，否则返回ERROR
 **/
status CreatBiTree(BiTree *T,char *definition)
{
    //以definition规则 先序创建一个二叉树
    CreatF(&(*T)->lchild,&definition);//从根结点创建
    if(*definition!='\0'){
        ClearBiTree(T);
        return ERROR;
    }
    return OK;
}

/**
 * 函数名称：ClearBiTree
 * 函数参数：二叉树T的地址
 * 函数功能：清空二叉树
 * 返回值：成功清空返回OK，否则返回ERROR
 **/
status ClearBiTree(BiTree *T)
{
    //清空二叉树
    if(!(*T)->lchild) return ERROR;//树已为空
    else{
        DestroyF(&((*T)->lchild));     //销毁数据域
        ((*T)->lchild)=NULL;          //头结点置空
        return OK;
    }
}

/**
 * 函数名称：BiTreeEmpty
 * 函数参数：二叉树T
 * 函数功能：判断二叉树是否为空
 * 返回值：二叉树为空返回OK，否则返回ERROR
 **/
status BiTreeEmpty(BiTree T)
{
    if(T->lchild==NULL) return OK;
    else return ERROR;
}

/**
 * 函数名称：BiTreeDepth
 * 函数参数：二叉树T
 * 函数功能：求取二叉树深度
 * 返回值：返回二叉树深度，求取失败返回ERROR
 **/
int BiTreeDepth(BiTree T)
{
    //返回二叉树最大深度
    if(T->lchild&&T->rchild)
        return 1+(BiTreeDepth(T->lchild)>BiTreeDepth(T->rchild)?BiTreeDepth(T->lchild):BiTreeDepth(T->rchild));
    if(T->lchild)
        return 1+BiTreeDepth(T->lchild);
    if(T->rchild)
        return 1+BiTreeDepth(T->rchild);
    return 0;
}

/**
 * 函数名称：Root
 * 函数参数：二叉树T，结点位序key，结点数据elem
 * 函数功能：用key与elem返回二叉树的头结点
 * 返回值：返回二叉树头结点成功则返回OK，失败则返回ERROR
 **/
status Root(BiTree T, int *key, ElemType *elem)
{
    //返回根的值
    if(T->lchild){//返回根值
        (*key)=T->lchild->key;
        (*elem)=T->lchild->data;
        return OK;
    }
    return ERROR;//空树
}

/**
 * Value的子函数
 **/
void ValueF(BiTree T,int key, ElemType *elem)
{
    //递归搜索关键字为key的结点
    if(T->key==key) (*elem)=T->data;
    if(T->lchild) ValueF(T->lchild,key,elem);
    if(T->rchild) ValueF(T->rchild,key,elem);
}
/**
 * 函数名称：Value
 * 函数参数：二叉树T，结点位序key，结点数据elem
 * 函数功能：用elem返回位序为key的结点的数据
 * 返回值：返回二叉树结点数据成功则返回OK，失败则返回ERROR
 **/
status Value(BiTree T,int key, ElemType *elem)
{
    //返回关键字为key的结点的数据
    (*elem)='\0';
    ValueF(T->lchild,key,elem);
    if((*elem)=='\0') return ERROR;//未找到
    return OK;
}

/**
 * Assign的子函数
 **/
void AssignF(BiTree *T,int key, ElemType *elem)
{
    //递归更改关键字为key的结点
    if((*T)->key==key) {
        (*T)->data=(*elem);
        (*elem)='\0';
    }
    if((*T)->lchild) AssignF(&(*T)->lchild,key,elem);
    if((*T)->rchild) AssignF(&(*T)->rchild,key,elem);
}
/**
 * 函数名称：Assign
 * 函数参数：二叉树T的地址，结点位序key，结点数据elem
 * 函数功能：用elem为位序为key的结点赋值
 * 返回值：为二叉树结点赋值成功返回OK，失败则返回ERROR
 **/
status Assign(BiTree *T,int key,ElemType elem)
{
    //结点赋值
    AssignF(T,key,&elem);
    if (elem=='\0') return OK;
    return ERROR;//赋值失败
}

/**
 * 函数名称：Parent
 * 函数参数：二叉树T，结点双亲位序key，结点位序key
 * 函数功能：查找结点的双亲
 * 返回值：若查找成功返回双亲结点地址，否则返回NULL
 **/
BiTree Parent(BiTree T,int head_key,int key)
{
    if(key==head_key) return NULL;//头结点无双亲返回NULL
    if((T->lchild&&T->lchild->key==key)||(T->rchild&&T->rchild->key==key)){
        return T;
    }
    //当前未找到 则递归搜索子节点关键字为key的结点
    BiTree temp=NULL;
    if(T->lchild) temp = Parent(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = Parent(T->rchild,head_key,key);
    if(temp) return temp;
    //未找到
    return NULL;
}

/**
 * 函数名称：LeftChild
 * 函数参数：二叉树T，结点位序key
 * 函数功能：查找结点的左孩子
 * 返回值：若查找成功返回左孩子结点地址，否则返回NULL
 **/
BiTree LeftChild(BiTree T,int key)
{
    if(T->key==key){//节点为所寻key 返回左孩子
        return T->lchild;//左孩子可能为空
    }
    //当前未找到 则递归搜索节点关键字为key的结点
    BiTree temp=NULL;
    if(T->lchild) temp = LeftChild(T->lchild,key);
    if(temp) return temp;
    if(T->rchild) temp = LeftChild(T->rchild,key);
    if(temp) return temp;
    return NULL;
}

/**
 * 函数名称：RightChild
 * 函数参数：二叉树T，结点位序key
 * 函数功能：查找结点的右孩子
 * 返回值：若查找成功返回右孩子结点地址，否则返回NULL
 **/
BiTree RightChild(BiTree T,int key)
{
    if(T->key==key){//节点为所寻key 返回右孩子
        return T->rchild;//右孩子可能为空
    }
    //当前未找到 则递归搜索节点关键字为key的结点
    BiTree temp=NULL;
    if(T->lchild) temp = RightChild(T->lchild,key);
    if(temp) return temp;
    if(T->rchild) temp = RightChild(T->rchild,key);
    if(temp) return temp;
    return NULL;
}

/**
 * 函数名称：LeftSibling
 * 函数参数：二叉树T，结点双亲位序，结点位序key
 * 函数功能：查找结点的左兄弟
 * 返回值：若查找成功返回左兄弟结点地址，否则返回NULL
 **/
BiTree LeftSibling(BiTree T,int head_key,int key)
{
    //寻找左兄弟
    if(key==head_key) return NULL;//头结点无兄弟结点
    if(T->rchild&&T->rchild->key==key){//右子节点为所寻key 返回左子结点
        return T->lchild;//左兄弟可能为空
    }
    //当前未找到 则递归搜索右子节点关键字为key的结点
    BiTree temp=NULL;
    if(T->lchild) temp = LeftSibling(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = LeftSibling(T->rchild,head_key,key);
    if(temp) return temp;
    return NULL;
}

/**
 * 函数名称：RightSibling
 * 函数参数：二叉树T，结点双亲位序，结点位序key
 * 函数功能：查找结点的右兄弟
 * 返回值：若查找成功返回右兄弟结点地址，否则返回NULL
 **/
BiTree RightSibling(BiTree T,int head_key,int key)
{
    //寻找右兄弟
    if(key==head_key) return NULL;//头结点无兄弟结点
    if(T->lchild&&T->lchild->key==key){//左子节点为所寻key 返回右子结点
        return T->rchild;//右兄弟可能为空
    }
    //当前未找到 则递归搜索左子节点关键字为key的结点
    BiTree temp=NULL;
    if(T->lchild) temp = RightSibling(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = RightSibling(T->rchild,head_key,key);
    if(temp) return temp;
    return NULL;
}

/**
 * InsertChild的子函数
 **/
BiTree Node(BiTree T, int key)
{
	//寻找结点
	if (T&&T->key==key) return T;
	BiTree temp = NULL;
	if (T->lchild) temp = Node(T->lchild, key);
	if (temp) return temp;
	if (T->rchild) temp = Node(T->rchild, key);
	if (temp) return temp;
	return NULL;
}
/**
 * InsertChild的子函数
 **/
status CreatInsertTree(BiTree *T_Insert,char *definition)
{
    //以definition规则 先序创建一个二叉树
    CreatF(T_Insert,&definition);//从根结点创建
    if(*definition!='\0'){
        ClearBiTree(T_Insert);
        return ERROR;
    }
    return OK;
}
/**
 * 函数名称：InsertChild
 * 函数参数：二叉树T的地址，插入结点位序key，左或右子树判断LR
 * 函数功能：在key结点下根据LR的取值插入左或右子树
 * 返回值：若插入子树成功返回OK，否则返回ERROR
 **/
status InsertChild(BiTree *T,int key,int LR)//插入子树
{
    BiTree T_Insert = NULL;//待插入子树的头结点（无头指针）
    char definition_insert[MAX];
    printf("      请输入用于生成子树的规则(definition)：\n      ");
    getchar();
    definition_insert[0]='\0';
    scanf("%[^\n]",definition_insert);
    if(*definition_insert=='\0'){
        printf("      输入definition序列不能为空！");
        return ERROR;
    }
    if(CreatInsertTree(&T_Insert,definition_insert)==OK){//创建待插入子树
        if(T_Insert->rchild) {
            printf("      创建得到的子树根节点应无右孩子，请检查创建的子树！\n");
            return ERROR;
        }
        if (Node(*T,key)==NULL) {
            printf("      未找到key对应结点！\n");
            return ERROR;
        }
        if(LR==0){//插入为左子树
            T_Insert->rchild = Node(*T,key)->lchild;
            Node(*T,key)->lchild = T_Insert;
        }
        if(LR==1){//插入右子树
            T_Insert->rchild = Node(*T,key)->rchild;
            Node(*T,key)->rchild = T_Insert;
        }
        return OK;
    }
    else{
        printf("      创建子树失败，请检查输入序列！\n");
        return ERROR;
    }
}

/**
 * 函数名称：DeleteChild
 * 函数参数：二叉树T的地址，删除结点位序key，左或右子树判断LR
 * 函数功能：在key结点下根据LR的取值删除左或右子树
 * 返回值：若删除子树成功返回OK，否则返回ERROR
 **/
status DeleteChild(BiTree *T, int key, int LR)//删除子树
{
	BiTree temp = Node(*T, key);
	if (temp == NULL) {
		printf("      未找到对应结点！\n");
		return ERROR;
	}
	if (LR == 0) {//删除左子树
		if (temp->lchild == NULL) {
			printf("      key对应结点左子树已为空！\n");
			return ERROR;
		}
		DestroyBiTree(&temp->lchild);
	}
	if (LR == 1) {//删除右子树
		if (temp->rchild == NULL) {
			printf("      key对应结点右子树已为空！\n");
			return ERROR;
		}
		DestroyBiTree(&temp->rchild);
	}
	return OK;
}

/**
 * 函数名称：PreOrderTraverse
 * 函数参数：二叉树T
 * 函数功能：前序遍历输出二叉树结点值
 * 返回值：若输出成功返回OK，否则返回ERROR
 **/
status PreOrderTraverse(BiTree T)//前序遍历
{
    printf("      key:%d data:%c\n",T->key,T->data);
    if(T->lchild) PreOrderTraverse(T->lchild);
    if(T->rchild) PreOrderTraverse(T->rchild);
    return OK;
}

/**
 * 函数名称：InOrderTraverse
 * 函数参数：二叉树T
 * 函数功能：中序遍历输出二叉树结点值
 * 返回值：若输出成功返回OK，否则返回ERROR
 **/
status InOrderTraverse(BiTree T)//中序遍历
{
    if(T->lchild) InOrderTraverse(T->lchild);
    printf("      key:%d data:%c\n",T->key,T->data);
    if(T->rchild) InOrderTraverse(T->rchild);
    return OK;
}

/**
 * 函数名称：PostOrderTraverse
 * 函数参数：二叉树T
 * 函数功能：后序遍历输出二叉树结点值
 * 返回值：若输出成功返回OK，否则返回ERROR
 **/
status PostOrderTraverse(BiTree T)//后序遍历
{
    if(T->lchild) PostOrderTraverse(T->lchild);
    if(T->rchild) PostOrderTraverse(T->rchild);
    printf("      key:%d data:%c\n",T->key,T->data);
    return OK;
}

/**
 * LevelOrderTraverse的子函数
 **/
void enter_seqqu(seqqueue *Q,BiTree T)
{
    //进队列
    if(Q->rear==MAX){
        printf("队列已满，二叉树过大\n");
    }
    else{
        Q->data[Q->rear]=T;
        Q->rear++;
    }
}
/**
 * LevelOrderTraverse的子函数
 **/
BiTree exit_seqqu(seqqueue *Q)
{
    //出队列
    if(Q->front == Q->rear){//队列已为空
        return NULL;
    }
    else{
        Q->front++;
        return Q->data[Q->front-1];
    }
}
/**
 * 函数名称：LevelOrderTraverse
 * 函数参数：二叉树T
 * 函数功能：层次遍历输出二叉树结点值
 * 返回值：若输出成功返回OK，否则返回ERROR
 **/
status LevelOrderTraverse(BiTree T)//传入头结点
{//层次遍历
    seqqueue Q;
    BiTree temp;
    Q.front=0;
    Q.rear=0;
    enter_seqqu(&Q,T);//树头结点进队列
    while(Q.front!=Q.rear){
        temp=exit_seqqu(&Q);//出队列并保存其值
        printf("      key:%d data:%c\n",temp->key,temp->data);

        if(temp->lchild){//左子结点进队列
            enter_seqqu(&Q,temp->lchild);
        }
        if(temp->rchild){//右子结点进队列
            enter_seqqu(&Q,temp->rchild);
        }
    }
    return OK;
}

/**
 * 函数名称：LoadList
 * 函数参数：二叉树T的地址，文件名filename
 * 函数功能：数据加载，将文件中数据读入，覆盖当前二叉树
 * 返回值：加载成功返回OK，加载失败返回ERROR
 **/
status LoadFile(BiTree *T,char *filename)
{
    BiTree temp=(BiTree)malloc(sizeof(BiTNode));
    temp -> lchild = NULL;
    char definition_load[MAX];//读取缓冲区
    definition_load[0]='\0';//初始化
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp==NULL) {
        printf("文件不存在！\n");
        return ERROR;
    }
    /*将文件中数据读入系统*/
    fscanf(fp,"%[^\n]",definition_load);//读取文件

    if(CreatBiTree(&temp,definition_load)==OK){//覆盖当前树
        key_static[list_num]=0;
        ClearBiTree(T);
        CreatBiTree(T,definition_load);
        fclose(fp);
        return OK;
    }
    else{
        printf("      序列definition中数据未全部使用！\n");
    }
    fclose(fp);
    return ERROR;
}

/**
 * SaveAsFile的子函数
 **/
void Save_PreOrderTraverse(BiTree T,char **d)//前序遍历将树转换为字符串序列
{
    *((*d)++) = T->data;
    if(!T->lchild) *((*d)++) = ' ';
    if(T->lchild) Save_PreOrderTraverse(T->lchild,d);
    if(!T->rchild) *((*d)++) = ' ';
    if(T->rchild) Save_PreOrderTraverse(T->rchild,d);
}
/**
 * 函数名称：SaveAsFile
 * 函数参数：二叉树T的地址，文件名filename
 * 函数功能：数据保存，将二叉树中数据保存至文件
 * 返回值：保存成功返回OK，加载失败返回ERROR
 **/
status SaveAsFile(BiTree T,char *filename)
{
    char *save_definition=(char*)malloc(1000*sizeof(char));
    *save_definition='\0';
    char **d=save_definition;
    Save_PreOrderTraverse(T,&d);
    *d='\0';

    FILE *fp;
    fp = fopen(filename, "wb+");
    /*将树中元素依次写入文件*/
    fprintf(fp, "%s", save_definition);
    fclose(fp);
    return OK;
}

/**
 * 函数名称：MulList
 * 函数参数：二叉树T的地址，森林表头M的地址，当前树序号list_num_cur，欲切换到的树序号list_num
 * 函数功能：切换操作树。
 * 返回值：成功切换返回OK，否则返回ERROR
 **/
status MulList(BiTree *T,MulNode *M,int list_num_cur,int list_num){
    //切换操作树，若目标表不存在则新建
    MulNode *mul_temp=NULL;//用于遍历多表结构
    MulNode *mul_new=NULL;//用于新建多表结点
    //存储表
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//给多表结构中的对应节点赋值，保存数据
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*T);
            break;
        }
    }

    //切换表（为表头T赋值）
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//查询多表结构中的对应节点，切换操作表
        if(mul_temp->next->list_num==list_num){//若查询成功，读入表
            (*T) = mul_temp->next->list_head;
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

    (*T) = mul_new -> list_head;

    return ERROR;
}
