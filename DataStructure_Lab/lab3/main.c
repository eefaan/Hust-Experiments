#include"bitree.h"

int key_static[MAX];//�������н���key
int list_num=1;//����ţ����֣�

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

    int list_num_cur=0;//��¼��ǰ�����
    int flag;//�������м�¼��������ֵ

    BiTree T=NULL;//��ǰ������ͷָ�� lchildָ����ڵ�
    BiTree temp=NULL;//������ʱ��Ų�ѯ���Ľ��
    ElemType elem;//���ڴ�������Ԫ��ֵ
    int key;//���ڴ���keyֵ
    int LR;//����ѡ��������������в���
    char definition[MAX];//����creat��
    char filename[MAX];

    int op=1;

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Binary Tree On Chain Structure \n");
        printf("      ��ǰ�����������Ϊ%d\n",list_num);
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
        printf("    ��ѡ����Ĳ���[0~23]:");
        scanf("%d",&op);

    switch(op){
        case 1:
            //��ʼ��
            if(T) printf("      �������ѳ�ʼ������ʼ��ʧ�ܣ�\n");
            else{
                if(InitBiTree(&T)==OK) printf("      ��������ʼ���ɹ���\n");
                else printf("      �洢�ռ䲻�㣬��ʼ��ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 2:
            //����
            if(!T) printf("      ������δ��ʼ����\n");
            else{
                if(DestroyBiTree(&T)==OK) printf("      ���������ٳɹ���\n");
                key_static[list_num]=0;//key��������
            }
            getchar();getchar();
            break;
        case 3:
            //����
            if(!T) printf("      ������δ��ʼ����\n");
            else{
                printf("      �������ַ���definition������ʽ�½�������\n      ����������abc   de  f  (��������keyֵ�����Զ����ɣ�����ѯ����Ӧkeyֵ�ɱ���������)\n      (���пո����ô�Ϊ�ս��)��");
                definition[0]='\0';
                getchar();
                scanf("%[^\n]",definition);
                if(definition[0]=='\0'){
                    printf("      ����definition���в���Ϊ�գ�\n");
                }
                else if(CreatBiTree(&T,&definition)==OK) printf("      �����������ɹ���\n");
                else printf("      ����ʧ�ܣ��ַ�����Ԫ��δȫ��ʹ�ã����鶨���Ƿ���Ϲ���\n");
            }
            getchar();getchar();
            break;
        case 4:
            //���
            if(!T) printf("      ������δ��ʼ����\n");
            else{
                if(ClearBiTree(&T)==OK) printf("      �������ÿճɹ���\n");
                else printf("      ��������Ϊ�գ��ÿ�ʧ�ܣ�\n");
                key_static[list_num]=0;//key��������
            }
            getchar();getchar();
            break;
        case 5:
            //�ж��Ƿ�Ϊ��
            if(!T) printf("      ������δ��ʼ����\n");//������
            else if(BiTreeEmpty(T)==OK) printf("      ������Ϊ�գ�\n");
            else printf("      ��������Ϊ�գ�\n");
            getchar();getchar();
            break;
        case 6:
            //�������������
            if(!T) printf("      ������δ��ʼ����\n");//������
            else{
                printf("      ������������Ϊ%d��\n",BiTreeDepth(T));
            }
            getchar();getchar();
            break;
        case 7:
            //����ֵ
            if(!T) printf("      ������δ��ʼ����\n");//������
            else{
                if(Root(T,&key,&elem)==OK) printf("      �������ĸ�keyΪ%d,����Ϊ%c",key,elem);
                else printf("      �ö�����Ϊ�������޸���\n");
            }
            getchar();getchar();
            break;
        case 8:
            //�ؼ���Ϊkey�Ľ�������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý������\n\n");
                printf("      key��");
                scanf("%d",&key);
                if(Value(T,key,&elem)==OK) printf("      ���Ա���keyΪ%d������Ԫ��ֵΪ%c\n",key,elem);
                else printf("      ������keyΪ%d�Ľ�㣡\n",key);
            }
            getchar();getchar();
            break;
        case 9:
            //���ؼ���Ϊkey�Ľ�㸳ֵ
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key������elem����Ϊ�ý�㸳ֵ\n\n");
                printf("      key��");
                scanf("%d",&key);
                getchar();
                printf("      elem��");
                scanf("%c",&elem);
                if(Assign(&T,key,elem)==OK) printf("      ���Ա���keyΪ%d������Ԫ��ֵ���ĳɹ�\n",key);
                else printf("      ������keyΪ%d�Ľ�㣡\n",key);
            }
            getchar();getchar();
            break;
        case 10:
            //����Parent���
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý���˫��\n\n");
                printf("      key��");
                scanf("%d",&key);
                temp=Parent(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      ���Ա���keyΪ%d�Ľ���˫�׽��keyΪ%d��dataΪ%c\n",key,temp->key,temp->data);
                else printf("      ������keyΪ%d�Ľ���ý��Ϊ���ڵ���˫�ף�\n",key);
            }
            temp=NULL;//�ÿ��ݴ���
            getchar();getchar();
            break;
        case 11:
            //����LeftChild���
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý������ӽ��\n\n");
                printf("      key��");
                scanf("%d",&key);
                temp=LeftChild(T->lchild,key);
                if(temp!=NULL) printf("      ���Ա���keyΪ%d�Ľ������ӽ��keyΪ%d��dataΪ%c\n",key,temp->key,temp->data);
                else printf("      ������keyΪ%d�Ľ���ý�������ӽ�㣡\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 12:
            //����RightChild���
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý������ӽ��\n\n");
                printf("      key��");
                scanf("%d",&key);
                temp=RightChild(T->lchild,key);
                if(temp!=NULL) printf("      ���Ա���keyΪ%d�Ľ����Һ��ӽ��keyΪ%d��dataΪ%c\n",key,temp->key,temp->data);
                else printf("      ������keyΪ%d�Ľ���ý�������ӽ�㣡\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 13:
            //����LeftSiBling���
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý������ֵܽ��\n\n");
                printf("      key��");
                scanf("%d",&key);
                temp=LeftSibling(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      ���Ա���keyΪ%d�Ľ������ֵܽ��keyΪ%d��dataΪ%c\n",key,temp->key,temp->data);
                else printf("      ������keyΪ%d�Ľ���ý�������ֵܽ�㣡\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 14:
            //����RightSiBling���
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key����Ϊ�����ظý������ֵܽ��\n\n");
                printf("      key��");
                scanf("%d",&key);
                temp=RightSibling(T->lchild,T->lchild->key,key);
                if(temp!=NULL) printf("      ���Ա���keyΪ%d�Ľ������ֵܽ��keyΪ%d��dataΪ%c\n",key,temp->key,temp->data);
                else printf("      ������keyΪ%d�Ľ���ý�������ֵܽ�㣡\n",key);
            }
            temp=NULL;
            getchar();getchar();
            break;
        case 15:
            //��������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key��ѡ��LR����Ϊ��������key��㴦����\n      ��LR=0����������������LR=1����������������\n\n");
                printf("      key��");
                scanf("%d",&key);
                getchar();
                printf("      LR��");
                scanf("%d",&LR);
                if(LR!=0&&LR!=1) printf("      ����LR���󣬷������˵���\n");
                else if(InsertChild(&T,key,LR)==OK) printf("      ����ɹ���\n");
                else printf("      ����ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 16:
            //ɾ������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else{
                printf("      ������ؼ���key��ѡ��LR����Ϊ��ɾ��key�������\n      ��LR=0��ɾ����������LR=1��ɾ����������\n\n");
                printf("      key��");
                scanf("%d",&key);
                getchar();
                printf("      LR��");
                scanf("%d",&LR);
                if(LR!=0&&LR!=1) printf("      ����LR���󣬷������˵���\n");
                else if(DeleteChild(&T,key,LR)==OK) printf("      ɾ���ɹ���\n");
                else printf("      ɾ��ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 17:
            //����������������������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else if(!T->lchild) {//�Ƿ�Ϊ����
                printf("      ������Ϊ�գ�\n");            }
            else{
                printf("      ��������������������\n");
                printf("--------------------------------------------\n");
                PreOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 18:
            //����������������������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else if(!T->lchild) {//�Ƿ�Ϊ����
                printf("      ������Ϊ�գ�\n");            }
            else{
                printf("      ��������������������\n");
                printf("--------------------------------------------\n");
                InOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 19:
            //����������������������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else if(!T->lchild) {//�Ƿ�Ϊ����
                printf("      ������Ϊ�գ�\n");            }
            else{
                printf("      �������ĺ�����������\n");
                printf("--------------------------------------------\n");
                PostOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 20:
            //��α������������������
            if(!T) printf("      ������δ��ʼ����\n");//��������
            else if(!T->lchild) {//�Ƿ�Ϊ����
                printf("      ������Ϊ�գ�\n");
            }
            else{
                printf("      �������Ĳ�α��������\n");
                printf("--------------------------------------------\n");
                LevelOrderTraverse(T->lchild);
                printf("--------------------------------------------\n");
            }
            getchar();getchar();
            break;
        case 21:
            //��ȡ�ļ�
            if(!T){
                printf("      ������δ��ʼ����\n");//��������
                getchar();
            }
            else{
                printf("      �����ļ��ж�ȡ���ݲ����ǵ�ǰ������.\n      ������Ҫ��ȡ���ļ���: ");getchar();
                gets(filename);
                if(LoadFile(&T,filename)==OK) printf("      �ļ���ȡ�ɹ���\n");
                else printf("      �ļ���ȡʧ�ܣ�\n");
            }
            getchar();
            break;
        case 22:
            //�洢�ļ�
            if(!T){
                printf("      ������δ��ʼ����\n");//��������
                getchar();
            }
            else if(!T->lchild){
                printf("      ������Ϊ�գ��޷��洢\n");
                getchar();
            }
            else{
                printf("      �������������ݱ���(д)Ϊ�ļ�\n      ������Ҫд����ļ���: ");getchar();
                gets(filename);
                if(SaveAsFile(T->lchild,filename)==OK) printf("      �ļ�д��ɹ���\n");
            }
            getchar();
            break;
        case 23:
            list_num_cur=list_num;//��¼��ǰ�����Դ洢����
            printf("      ������Ҫ�л���������ţ�");
            scanf("%d",&list_num);

            flag=MulList(&T,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      �л��ɹ�����ǰ������Ϊ��%d\n",list_num);
            else if(flag==ERROR) printf("      ��%d�����ڣ���Ϊ���½���%d���л�(δ��ʼ��)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//��������ʧ��
                printf("      �ռ䲻�㣬������ʧ�ܣ�\n");
                list_num=list_num_cur;//��ǰ�������������ǰ
            }

            //������������
            printf("\n------------------- all list --------------------\n");
            printf("      ��ǰ����%d�����ɹ�����\n      �����Ϊ(������ʱ������)��\n      ",MulList_head->list_num);
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
 * �������ƣ�InitBiTree
 * ����������������T�ĵ�ַ
 * �������ܣ�����һ���յĶ�����
 * ����ֵ���ɹ����췵��OK�����򷵻�ERROR
 **/
status InitBiTree(BiTree *T)
{
    //����һ��������
    *T = (BiTree)malloc(sizeof(BiTNode));
    if(!(*T)) return ERROR;      //�洢����ʧ��
    (*T)->lchild=NULL;           //������ͷ����ÿ�
    (*T)->rchild=NULL;           //���ӽ���ÿ�
    return OK;
}

/**
 * DestroyBiTree���Ӻ���
 **/
void DestroyF(BiTree *T)
{
    //�ݹ��ͷŽ��ռ�
    if((*T)->lchild) DestroyF(&((*T)->lchild));
    if((*T)->rchild) DestroyF(&((*T)->rchild));
    free(*T);
}
/**
 * �������ƣ�DestroyBiTree
 * ����������������T�ĵ�ַ
 * �������ܣ�ɾ��������
 * ����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
 **/
status DestroyBiTree(BiTree *T)
{
    //���ٶ�����
    DestroyF(T);
    (*T)=NULL;
    return OK;
}

/**
 * CreatBiTree���Ӻ���
 **/
void CreatF(BiTree *T,char **d)
{
    //�ݹ鸳ֵ
    if (**d ==' ') {
        (*T)=NULL;
        (*d)++;
    }
    else
    {
        (*T)=(BiTree)malloc(sizeof(BiTNode));
        (*T)->key =key_static[list_num]++;
        (*T)->data=*((*d)++);                //���ɸ����
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;

        if(**d!='\0')CreatF(&(*T)->lchild,d); //�ݹ鹹��������
        if(**d!='\0')CreatF(&(*T)->rchild,d); //�ݹ鹹��������
    }
}
/**
 * �������ƣ�CreatBiTree
 * ����������������T�ĵ�ַ����������definition
 * �������ܣ�������������definition����������
 * ����ֵ���ɹ���������OK�����򷵻�ERROR
 **/
status CreatBiTree(BiTree *T,char *definition)
{
    //��definition���� ���򴴽�һ��������
    CreatF(&(*T)->lchild,&definition);//�Ӹ���㴴��
    if(*definition!='\0'){
        ClearBiTree(T);
        return ERROR;
    }
    return OK;
}

/**
 * �������ƣ�ClearBiTree
 * ����������������T�ĵ�ַ
 * �������ܣ���ն�����
 * ����ֵ���ɹ���շ���OK�����򷵻�ERROR
 **/
status ClearBiTree(BiTree *T)
{
    //��ն�����
    if(!(*T)->lchild) return ERROR;//����Ϊ��
    else{
        DestroyF(&((*T)->lchild));     //����������
        ((*T)->lchild)=NULL;          //ͷ����ÿ�
        return OK;
    }
}

/**
 * �������ƣ�BiTreeEmpty
 * ����������������T
 * �������ܣ��ж϶������Ƿ�Ϊ��
 * ����ֵ��������Ϊ�շ���OK�����򷵻�ERROR
 **/
status BiTreeEmpty(BiTree T)
{
    if(T->lchild==NULL) return OK;
    else return ERROR;
}

/**
 * �������ƣ�BiTreeDepth
 * ����������������T
 * �������ܣ���ȡ���������
 * ����ֵ�����ض�������ȣ���ȡʧ�ܷ���ERROR
 **/
int BiTreeDepth(BiTree T)
{
    //���ض�����������
    if(T->lchild&&T->rchild)
        return 1+(BiTreeDepth(T->lchild)>BiTreeDepth(T->rchild)?BiTreeDepth(T->lchild):BiTreeDepth(T->rchild));
    if(T->lchild)
        return 1+BiTreeDepth(T->lchild);
    if(T->rchild)
        return 1+BiTreeDepth(T->rchild);
    return 0;
}

/**
 * �������ƣ�Root
 * ����������������T�����λ��key���������elem
 * �������ܣ���key��elem���ض�������ͷ���
 * ����ֵ�����ض�����ͷ���ɹ��򷵻�OK��ʧ���򷵻�ERROR
 **/
status Root(BiTree T, int *key, ElemType *elem)
{
    //���ظ���ֵ
    if(T->lchild){//���ظ�ֵ
        (*key)=T->lchild->key;
        (*elem)=T->lchild->data;
        return OK;
    }
    return ERROR;//����
}

/**
 * Value���Ӻ���
 **/
void ValueF(BiTree T,int key, ElemType *elem)
{
    //�ݹ������ؼ���Ϊkey�Ľ��
    if(T->key==key) (*elem)=T->data;
    if(T->lchild) ValueF(T->lchild,key,elem);
    if(T->rchild) ValueF(T->rchild,key,elem);
}
/**
 * �������ƣ�Value
 * ����������������T�����λ��key���������elem
 * �������ܣ���elem����λ��Ϊkey�Ľ�������
 * ����ֵ�����ض�����������ݳɹ��򷵻�OK��ʧ���򷵻�ERROR
 **/
status Value(BiTree T,int key, ElemType *elem)
{
    //���عؼ���Ϊkey�Ľ�������
    (*elem)='\0';
    ValueF(T->lchild,key,elem);
    if((*elem)=='\0') return ERROR;//δ�ҵ�
    return OK;
}

/**
 * Assign���Ӻ���
 **/
void AssignF(BiTree *T,int key, ElemType *elem)
{
    //�ݹ���Ĺؼ���Ϊkey�Ľ��
    if((*T)->key==key) {
        (*T)->data=(*elem);
        (*elem)='\0';
    }
    if((*T)->lchild) AssignF(&(*T)->lchild,key,elem);
    if((*T)->rchild) AssignF(&(*T)->rchild,key,elem);
}
/**
 * �������ƣ�Assign
 * ����������������T�ĵ�ַ�����λ��key���������elem
 * �������ܣ���elemΪλ��Ϊkey�Ľ�㸳ֵ
 * ����ֵ��Ϊ��������㸳ֵ�ɹ�����OK��ʧ���򷵻�ERROR
 **/
status Assign(BiTree *T,int key,ElemType elem)
{
    //��㸳ֵ
    AssignF(T,key,&elem);
    if (elem=='\0') return OK;
    return ERROR;//��ֵʧ��
}

/**
 * �������ƣ�Parent
 * ����������������T�����˫��λ��key�����λ��key
 * �������ܣ����ҽ���˫��
 * ����ֵ�������ҳɹ�����˫�׽���ַ�����򷵻�NULL
 **/
BiTree Parent(BiTree T,int head_key,int key)
{
    if(key==head_key) return NULL;//ͷ�����˫�׷���NULL
    if((T->lchild&&T->lchild->key==key)||(T->rchild&&T->rchild->key==key)){
        return T;
    }
    //��ǰδ�ҵ� ��ݹ������ӽڵ�ؼ���Ϊkey�Ľ��
    BiTree temp=NULL;
    if(T->lchild) temp = Parent(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = Parent(T->rchild,head_key,key);
    if(temp) return temp;
    //δ�ҵ�
    return NULL;
}

/**
 * �������ƣ�LeftChild
 * ����������������T�����λ��key
 * �������ܣ����ҽ�������
 * ����ֵ�������ҳɹ��������ӽ���ַ�����򷵻�NULL
 **/
BiTree LeftChild(BiTree T,int key)
{
    if(T->key==key){//�ڵ�Ϊ��Ѱkey ��������
        return T->lchild;//���ӿ���Ϊ��
    }
    //��ǰδ�ҵ� ��ݹ������ڵ�ؼ���Ϊkey�Ľ��
    BiTree temp=NULL;
    if(T->lchild) temp = LeftChild(T->lchild,key);
    if(temp) return temp;
    if(T->rchild) temp = LeftChild(T->rchild,key);
    if(temp) return temp;
    return NULL;
}

/**
 * �������ƣ�RightChild
 * ����������������T�����λ��key
 * �������ܣ����ҽ����Һ���
 * ����ֵ�������ҳɹ������Һ��ӽ���ַ�����򷵻�NULL
 **/
BiTree RightChild(BiTree T,int key)
{
    if(T->key==key){//�ڵ�Ϊ��Ѱkey �����Һ���
        return T->rchild;//�Һ��ӿ���Ϊ��
    }
    //��ǰδ�ҵ� ��ݹ������ڵ�ؼ���Ϊkey�Ľ��
    BiTree temp=NULL;
    if(T->lchild) temp = RightChild(T->lchild,key);
    if(temp) return temp;
    if(T->rchild) temp = RightChild(T->rchild,key);
    if(temp) return temp;
    return NULL;
}

/**
 * �������ƣ�LeftSibling
 * ����������������T�����˫��λ�򣬽��λ��key
 * �������ܣ����ҽ������ֵ�
 * ����ֵ�������ҳɹ��������ֵܽ���ַ�����򷵻�NULL
 **/
BiTree LeftSibling(BiTree T,int head_key,int key)
{
    //Ѱ�����ֵ�
    if(key==head_key) return NULL;//ͷ������ֵܽ��
    if(T->rchild&&T->rchild->key==key){//���ӽڵ�Ϊ��Ѱkey �������ӽ��
        return T->lchild;//���ֵܿ���Ϊ��
    }
    //��ǰδ�ҵ� ��ݹ��������ӽڵ�ؼ���Ϊkey�Ľ��
    BiTree temp=NULL;
    if(T->lchild) temp = LeftSibling(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = LeftSibling(T->rchild,head_key,key);
    if(temp) return temp;
    return NULL;
}

/**
 * �������ƣ�RightSibling
 * ����������������T�����˫��λ�򣬽��λ��key
 * �������ܣ����ҽ������ֵ�
 * ����ֵ�������ҳɹ��������ֵܽ���ַ�����򷵻�NULL
 **/
BiTree RightSibling(BiTree T,int head_key,int key)
{
    //Ѱ�����ֵ�
    if(key==head_key) return NULL;//ͷ������ֵܽ��
    if(T->lchild&&T->lchild->key==key){//���ӽڵ�Ϊ��Ѱkey �������ӽ��
        return T->rchild;//���ֵܿ���Ϊ��
    }
    //��ǰδ�ҵ� ��ݹ��������ӽڵ�ؼ���Ϊkey�Ľ��
    BiTree temp=NULL;
    if(T->lchild) temp = RightSibling(T->lchild,head_key,key);
    if(temp) return temp;
    if(T->rchild) temp = RightSibling(T->rchild,head_key,key);
    if(temp) return temp;
    return NULL;
}

/**
 * InsertChild���Ӻ���
 **/
BiTree Node(BiTree T, int key)
{
	//Ѱ�ҽ��
	if (T&&T->key==key) return T;
	BiTree temp = NULL;
	if (T->lchild) temp = Node(T->lchild, key);
	if (temp) return temp;
	if (T->rchild) temp = Node(T->rchild, key);
	if (temp) return temp;
	return NULL;
}
/**
 * InsertChild���Ӻ���
 **/
status CreatInsertTree(BiTree *T_Insert,char *definition)
{
    //��definition���� ���򴴽�һ��������
    CreatF(T_Insert,&definition);//�Ӹ���㴴��
    if(*definition!='\0'){
        ClearBiTree(T_Insert);
        return ERROR;
    }
    return OK;
}
/**
 * �������ƣ�InsertChild
 * ����������������T�ĵ�ַ��������λ��key������������ж�LR
 * �������ܣ���key����¸���LR��ȡֵ�������������
 * ����ֵ�������������ɹ�����OK�����򷵻�ERROR
 **/
status InsertChild(BiTree *T,int key,int LR)//��������
{
    BiTree T_Insert = NULL;//������������ͷ��㣨��ͷָ�룩
    char definition_insert[MAX];
    printf("      �������������������Ĺ���(definition)��\n      ");
    getchar();
    definition_insert[0]='\0';
    scanf("%[^\n]",definition_insert);
    if(*definition_insert=='\0'){
        printf("      ����definition���в���Ϊ�գ�");
        return ERROR;
    }
    if(CreatInsertTree(&T_Insert,definition_insert)==OK){//��������������
        if(T_Insert->rchild) {
            printf("      �����õ����������ڵ�Ӧ���Һ��ӣ����鴴����������\n");
            return ERROR;
        }
        if (Node(*T,key)==NULL) {
            printf("      δ�ҵ�key��Ӧ��㣡\n");
            return ERROR;
        }
        if(LR==0){//����Ϊ������
            T_Insert->rchild = Node(*T,key)->lchild;
            Node(*T,key)->lchild = T_Insert;
        }
        if(LR==1){//����������
            T_Insert->rchild = Node(*T,key)->rchild;
            Node(*T,key)->rchild = T_Insert;
        }
        return OK;
    }
    else{
        printf("      ��������ʧ�ܣ������������У�\n");
        return ERROR;
    }
}

/**
 * �������ƣ�DeleteChild
 * ����������������T�ĵ�ַ��ɾ�����λ��key������������ж�LR
 * �������ܣ���key����¸���LR��ȡֵɾ�����������
 * ����ֵ����ɾ�������ɹ�����OK�����򷵻�ERROR
 **/
status DeleteChild(BiTree *T, int key, int LR)//ɾ������
{
	BiTree temp = Node(*T, key);
	if (temp == NULL) {
		printf("      δ�ҵ���Ӧ��㣡\n");
		return ERROR;
	}
	if (LR == 0) {//ɾ��������
		if (temp->lchild == NULL) {
			printf("      key��Ӧ�����������Ϊ�գ�\n");
			return ERROR;
		}
		DestroyBiTree(&temp->lchild);
	}
	if (LR == 1) {//ɾ��������
		if (temp->rchild == NULL) {
			printf("      key��Ӧ�����������Ϊ�գ�\n");
			return ERROR;
		}
		DestroyBiTree(&temp->rchild);
	}
	return OK;
}

/**
 * �������ƣ�PreOrderTraverse
 * ����������������T
 * �������ܣ�ǰ�����������������ֵ
 * ����ֵ��������ɹ�����OK�����򷵻�ERROR
 **/
status PreOrderTraverse(BiTree T)//ǰ�����
{
    printf("      key:%d data:%c\n",T->key,T->data);
    if(T->lchild) PreOrderTraverse(T->lchild);
    if(T->rchild) PreOrderTraverse(T->rchild);
    return OK;
}

/**
 * �������ƣ�InOrderTraverse
 * ����������������T
 * �������ܣ��������������������ֵ
 * ����ֵ��������ɹ�����OK�����򷵻�ERROR
 **/
status InOrderTraverse(BiTree T)//�������
{
    if(T->lchild) InOrderTraverse(T->lchild);
    printf("      key:%d data:%c\n",T->key,T->data);
    if(T->rchild) InOrderTraverse(T->rchild);
    return OK;
}

/**
 * �������ƣ�PostOrderTraverse
 * ����������������T
 * �������ܣ��������������������ֵ
 * ����ֵ��������ɹ�����OK�����򷵻�ERROR
 **/
status PostOrderTraverse(BiTree T)//�������
{
    if(T->lchild) PostOrderTraverse(T->lchild);
    if(T->rchild) PostOrderTraverse(T->rchild);
    printf("      key:%d data:%c\n",T->key,T->data);
    return OK;
}

/**
 * LevelOrderTraverse���Ӻ���
 **/
void enter_seqqu(seqqueue *Q,BiTree T)
{
    //������
    if(Q->rear==MAX){
        printf("��������������������\n");
    }
    else{
        Q->data[Q->rear]=T;
        Q->rear++;
    }
}
/**
 * LevelOrderTraverse���Ӻ���
 **/
BiTree exit_seqqu(seqqueue *Q)
{
    //������
    if(Q->front == Q->rear){//������Ϊ��
        return NULL;
    }
    else{
        Q->front++;
        return Q->data[Q->front-1];
    }
}
/**
 * �������ƣ�LevelOrderTraverse
 * ����������������T
 * �������ܣ���α���������������ֵ
 * ����ֵ��������ɹ�����OK�����򷵻�ERROR
 **/
status LevelOrderTraverse(BiTree T)//����ͷ���
{//��α���
    seqqueue Q;
    BiTree temp;
    Q.front=0;
    Q.rear=0;
    enter_seqqu(&Q,T);//��ͷ��������
    while(Q.front!=Q.rear){
        temp=exit_seqqu(&Q);//�����в�������ֵ
        printf("      key:%d data:%c\n",temp->key,temp->data);

        if(temp->lchild){//���ӽ�������
            enter_seqqu(&Q,temp->lchild);
        }
        if(temp->rchild){//���ӽ�������
            enter_seqqu(&Q,temp->rchild);
        }
    }
    return OK;
}

/**
 * �������ƣ�LoadList
 * ����������������T�ĵ�ַ���ļ���filename
 * �������ܣ����ݼ��أ����ļ������ݶ��룬���ǵ�ǰ������
 * ����ֵ�����سɹ�����OK������ʧ�ܷ���ERROR
 **/
status LoadFile(BiTree *T,char *filename)
{
    BiTree temp=(BiTree)malloc(sizeof(BiTNode));
    temp -> lchild = NULL;
    char definition_load[MAX];//��ȡ������
    definition_load[0]='\0';//��ʼ��
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp==NULL) {
        printf("�ļ������ڣ�\n");
        return ERROR;
    }
    /*���ļ������ݶ���ϵͳ*/
    fscanf(fp,"%[^\n]",definition_load);//��ȡ�ļ�

    if(CreatBiTree(&temp,definition_load)==OK){//���ǵ�ǰ��
        key_static[list_num]=0;
        ClearBiTree(T);
        CreatBiTree(T,definition_load);
        fclose(fp);
        return OK;
    }
    else{
        printf("      ����definition������δȫ��ʹ�ã�\n");
    }
    fclose(fp);
    return ERROR;
}

/**
 * SaveAsFile���Ӻ���
 **/
void Save_PreOrderTraverse(BiTree T,char **d)//ǰ���������ת��Ϊ�ַ�������
{
    *((*d)++) = T->data;
    if(!T->lchild) *((*d)++) = ' ';
    if(T->lchild) Save_PreOrderTraverse(T->lchild,d);
    if(!T->rchild) *((*d)++) = ' ';
    if(T->rchild) Save_PreOrderTraverse(T->rchild,d);
}
/**
 * �������ƣ�SaveAsFile
 * ����������������T�ĵ�ַ���ļ���filename
 * �������ܣ����ݱ��棬�������������ݱ������ļ�
 * ����ֵ������ɹ�����OK������ʧ�ܷ���ERROR
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
    /*������Ԫ������д���ļ�*/
    fprintf(fp, "%s", save_definition);
    fclose(fp);
    return OK;
}

/**
 * �������ƣ�MulList
 * ����������������T�ĵ�ַ��ɭ�ֱ�ͷM�ĵ�ַ����ǰ�����list_num_cur�����л����������list_num
 * �������ܣ��л���������
 * ����ֵ���ɹ��л�����OK�����򷵻�ERROR
 **/
status MulList(BiTree *T,MulNode *M,int list_num_cur,int list_num){
    //�л�����������Ŀ����������½�
    MulNode *mul_temp=NULL;//���ڱ������ṹ
    MulNode *mul_new=NULL;//�����½������
    //�洢��
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//�����ṹ�еĶ�Ӧ�ڵ㸳ֵ����������
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*T);
            break;
        }
    }

    //�л���Ϊ��ͷT��ֵ��
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//��ѯ���ṹ�еĶ�Ӧ�ڵ㣬�л�������
        if(mul_temp->next->list_num==list_num){//����ѯ�ɹ��������
            (*T) = mul_temp->next->list_head;
            return OK;
        }
    }
    //����ѯʧ�ܣ��ڶ��ṹ���½�����ʱmul_temp->nextָ���Ѿ�ָ������β��NULL
    mul_new = (MulNode *)malloc(sizeof(MulNode));
    if (mul_new==NULL) return OVERFLOW;   //����ռ�ʧ��

    mul_new -> list_num = list_num;//��ֵ����
    mul_new -> list_head = NULL;//�±�ͷ�ڵ��ÿ�
    mul_new -> next = NULL;//�½ڵ�next�ÿ�

    mul_temp -> next = mul_new;//Ϊ�½ڵ㸳ֵ
    M->list_num++;//��¼������+1

    (*T) = mul_new -> list_head;

    return ERROR;
}
