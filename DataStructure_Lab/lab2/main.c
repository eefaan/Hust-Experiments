#include "LinearTable.h"

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

    LinkList L=NULL;//��ǰ���ͷ

    int list_num=1;//�����
    int list_num_cur=0;//��¼��ǰ�����
    int op=1;
    int i;//λ��
    int e;//����λ��i��ֵe
    int cur;//��ҪѰ��ǰ�����̵�����
    int pre_e;//����ǰ��
    int next_e;//���غ��
    int flag;//�������м�¼��������ֵ
    char filename[20];

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Chain Structure \n");
        printf("      ��ǰ�����ı����Ϊ%d\n",list_num);
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
        printf("    ��ѡ����Ĳ���[0~15]:");
        scanf("%d",&op);

    switch(op){
        case 1:
            //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
            if(L) printf("      ���Ա��ѳ�ʼ������ʼ��ʧ�ܣ�\n");
            else{
                if(IntiaList(&L)==OK) printf("      ���Ա����ɹ���\n");
                else printf("      ���Ա��Ѵ��ڻ�洢�ռ䲻�㣬����ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 2:
            //printf("\n----DestroyList���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");
            else{
                if(DestroyList(&L)==OK) printf("      ���Ա����ٳɹ���\n");
            }
            getchar();getchar();
            break;
        case 3:
            //printf("\n----ClearList���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");
            else{
                if(ClearList(&L)==OK) printf("      ���Ա��ÿճɹ���\n");
                else printf("      ���Ա���Ϊ�գ��ÿ�ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 4:
            //printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else if(ListEmpty(L)==OK) printf("      ���Ա�Ϊ�գ�\n");
            else printf("      ���Ա�Ϊ�գ�\n");
            getchar();getchar();
            break;
        case 5:
            //printf("\n----ListLength���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ���Ա���Ϊ%d��\n",ListLength(L));
            }
            getchar();getchar();
            break;
        case 6:
            //printf("\n----GetElem���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ������λ�򣬽�Ϊ�����ظ�λ������Ԫ�ص�ֵ\n\n");
                printf("      λ��");
                scanf("%d",&i);
                if(GetElem(L,i,&e)==OK) printf("      ���Ա��е�%d������Ԫ�ص�ֵΪ%d\n",i,e);
                else printf("      ����Խ�磬��λ�򲻴��ڣ�\n");
            }
            getchar();getchar();
            break;
        case 7:
            //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ����ݵ�λ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&e);
                if(LocateElem(L,e,&i)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�ص�λ��Ϊ%d\n",e,i);
                else printf("      ���Ա���δ��ѯ��������Ԫ�أ�\n");
            }
            getchar();getchar();
            break;
        case 8:
            //printf("\n----PriorElem���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ�����Ԫ�ص�ǰ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&cur);
                if(PriorElem(L,cur, &pre_e)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�ص�ǰ��Ϊ%d��\n",cur,pre_e);
                else printf("      ���Ա���δ��ѯ��������Ԫ�ػ������Ԫ����ǰ����\n");
            }
            getchar();getchar();
            break;
        case 9:
            //printf("\n----NextElem���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ�����Ԫ�صĺ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&cur);
                if(NextElem(L,cur, &next_e)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�صĺ��Ϊ%d��\n",cur,next_e);
                else printf("      ���Ա���δ��ѯ��������Ԫ�ػ������Ԫ���޺�̣�\n");
            }
            getchar();getchar();
            break;
        case 10:
            //printf("\n----ListInsert���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ��Ҫ��������Ԫ�أ������뽫Ҫ���������Ԫ�ص�λ����ֵ\n\n");
                printf("      λ��");
                scanf("%d",&i);
                printf("      ֵ��");
                scanf("%d",&e);
                if(ListInsert(&L,i,e)==OK) printf("      ����Ԫ�ز���ɹ���\n");
                else printf("      Խ�磬����Ԫ�ز���ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 11:
            //printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                printf("      ��Ҫɾ������Ԫ�أ������뽫Ҫɾ��������Ԫ�ص�λ��\n\n");
                printf("      λ��");
                scanf("%d",&i);
                if(ListDelete(&L,i,&e)==OK) printf("      ����Ԫ��ɾ���ɹ���ɾ����Ԫ��Ϊ%d��\n",e);
                else printf("      Խ�磬����Ԫ��ɾ��ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
            if(!L) printf("      ���Ա�δ��ʼ����\n");//������
            else{
                ListTrabverse(L);
                if(!L->next) printf("      ���Ա��ǿձ�\n");
            }
            getchar();getchar();
            break;
        case 13:
            //printf("\n----��ȡ�ļ����ܴ�ʵ�֣�\n");
            if(!L){
                printf("      ���Ա�δ��ʼ����\n");//������
                getchar();
            }
            else{
                printf("      �����ļ��ж�ȡ���ݲ����뵱ǰ���Ա����.\n      ������Ҫ��ȡ���ļ���: ");getchar();
                gets(filename);
                if(LoadFile(L,filename)==OK) printf("      �ļ���ȡ�ɹ�����Ϊ%d.\n",ListLength(L));
                else printf("      �ļ���ȡʧ�ܣ��ļ������ڻ�����������\n");
            }
            getchar();
            break;
        case 14:
            //printf("\n----����ļ����ܴ�ʵ�֣�\n");
            if(!L){
                printf("      ���Ա�δ��ʼ����\n");//������
                getchar();
            }
            else{
                printf("      �����Ա������ݱ���(д)Ϊ�ļ�\n      ������Ҫд����ļ���: ");getchar();
                gets(filename);
                if(SaveAsFile(L,filename)==OK) printf("      �ļ�д��ɹ�.\n");
            }
            getchar();
            break;
        case 15:
            //printf("\n----������ܴ�ʵ�֣�\n");
            list_num_cur=list_num;//��¼��ǰ�����Դ洢����
            printf("      ������Ҫ�л����ı���ţ�");
            scanf("%d",&list_num);

            flag=MulList(&L,MulList_head,list_num_cur,list_num);
            if(flag==OK) printf("      �л��ɹ�����ǰ������Ϊ��%d\n",list_num);
            else if(flag==ERROR) printf("      ��%d�����ڣ���Ϊ���½���%d���л�(δ��ʼ��)\n",list_num,list_num);
            else if(flag==OVERFLOW) {//�±���ʧ��
                printf("      �ռ䲻�㣬���Ա���ʧ�ܣ�\n");
                list_num=list_num_cur;//��ǰ�������������ǰ
            }

            //������б���
            printf("\n------------------- all list --------------------\n");
            printf("      ��ǰ����%d�����Ա�ɹ�����\n      �����Ϊ(������ʱ������)��\n      ",MulList_head->list_num);
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
 * �������ƣ�InitiaList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ�����һ���յ����Ա�
 * ����ֵ���ɹ����췵��OK�����򷵻�ERROR
 **/
status IntiaList(LinkList *L){
    //����һ�������Ա�
	*L = (LinkList)malloc(sizeof (LNode));
    if(!(*L)) return ERROR;      //�洢����ʧ��
    (*L) -> next = NULL;           //nextָ��ָ��-���Ա��ÿ�
	return OK;
}

/**
 * �������ƣ�DestroyList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ�ɾ�����Ա�
 * ����ֵ���ɹ����ٷ���OK�����򷵻�ERROR
 **/
status DestroyList(LinkList *L){
    //�������Ա�
    LinkList temp;
    LinkList tail;
    for(tail=*L;tail->next!=NULL;){//�ͷŽ��ռ�
        temp=tail;
        tail=tail->next;
        free(temp);
    }
    free(tail);
    (*L)=NULL;
    return OK;
}

/**
 * �������ƣ�ClearList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ��������Ա�
 * ����ֵ���ɹ��ÿշ���OK�����򷵻�ERROR
 **/
status ClearList(LinkList *L){
    //��L����Ϊ�ձ�
    if((*L)->next==NULL) return ERROR;//���Ա���Ϊ��
    LinkList temp;
    LinkList tail;
    for(tail=(*L)->next;tail->next!=NULL;){//�ͷ����ݽ��ռ�
        temp=tail;
        tail=tail->next;
        free(temp);
    }
    free(tail);
    (*L)->next=NULL;//����Ϊ�ձ�
    return OK;
}

/**
 * �������ƣ�ListEmpty
 * �������������Ա�L
 * �������ܣ��ж����Ա��Ƿ�Ϊ��
 * ����ֵ����LΪ�ձ��򷵻�OK�����򷵻�ERROR
 **/
status ListEmpty(LinkList L){
    //�ж�L�Ƿ�Ϊ�ձ����򷵻�OK�����򷵻�ERROR
    if(!L->next) return OK;
    return ERROR;
}

/**
 * �������ƣ�ListLength
 * �������������Ա�L��
 * �������ܣ��������Ա�L������Ԫ�ظ�����
 * ����ֵ���ɹ�����L������Ԫ�ظ�����ʧ�ܷ���ERROR
 **/
int ListLength(LinkList L){
    //����˳�����Ա���
    int length;
    for(length=0;L->next!=NULL;L=L->next){
        length++;
    }
    return length;
}

/**
 * �������ƣ�GetElem
 * �������������Ա�L����i�����ݣ�eΪ��i�����ݣ�
 * �������ܣ����Ҳ���e����L�е�i��Ԫ�ص�ֵ��
 * ����ֵ���ɹ��򷵻�OK�����򷵻�ERROR
 **/
status GetElem(LinkList L,int i,ElemType *e){
    //��e����L�е�i������Ԫ�ص�ֵ
    if(i<1 || i>ListLength(L)) return ERROR;//Խ��
    for(;i>0;i--){
        L=L->next;
    }
    (*e)=L->data;
    return OK;
}

/**
 * �������ƣ�LocateElem
 * �������������Ա�L����i�����ݣ�eΪ��i�����ݣ�
 * �������ܣ�����L����e��ͬ�������ڵ�λ����i���ظ�λ��
 * ����ֵ���ɹ��򷵻�OK���������򷵻�ERROR
 **/
status LocateElem(LinkList L,ElemType e,ElemType *i){//�򻯹�
    //���Ա�L�Ѵ��ڣ���i����L�е�һ��e��λ����������e�����ڣ�����ERROR
    int temp;
    int length = ListLength(L);//ֱ��ʹ��L��������LISTLENGTH��ֵ��仯��ʹ��length�洢���Ա���

    for(temp=0;temp<length;temp++){
        L=L->next;
        if(L->data==e){
            (*i)=temp+1;
            return OK;
        }
    }

    return ERROR;//δ�ҵ�
}

/**
 * �������ƣ�PriorElem
 * �������������Ա�L�����ҵ�����cur,ǰ��pre_e��
 * �������ܣ�����L����cur��ͬ�ĵ�һ�����ݣ�����pre_e������ǰ��
 * ����ֵ���ɹ��򷵻�OK������ǰ���Լ���������򷵻�ERROR
 **/
status PriorElem(LinkList L,ElemType cur,ElemType *pre_e){
    //��cur��L������Ԫ���Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre.e�޶���
    int cur_e;//curԪ�ص�λ��

    if(LocateElem(L,cur,&cur_e)==OK){//��Ԫ�ش���
        if(cur_e!=1){//���ǵ�һ��Ԫ��
            GetElem(L,cur_e-1,pre_e);//��pre_e����ǰ��Ԫ��
            return OK;
        }
    }

    return ERROR;//Ԫ�ز����ڻ�����ǰ��
}

/**
 * �������ƣ�NextElem
 * �������������Ա�L�����ҵ�����cur,���next_e��
 * �������ܣ�����L����cur��ͬ�ĵ�һ�����ݣ�����next_e��������
 * ����ֵ���ɹ��򷵻�OK�����޺���Լ���������򷵻�ERROR
 **/
status NextElem(LinkList L,ElemType cur,ElemType *next_e){
    //��cur��L������Ԫ���Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next.e�޶���
    int cur_e;//curԪ�ص�λ��

    if(LocateElem(L,cur,&cur_e)==OK){//��Ԫ�ش���
        if(cur_e!=ListLength(L)){//�������һ��Ԫ��
            GetElem(L,cur_e+1,next_e);//��next_e���غ��Ԫ��
            return OK;
        }
    }

    return ERROR;
}

/**
 * �������ƣ�ListInsert
 * �������������Ա�L�ĵ�ַ�������λ��i�����������Ԫ��e��
 * �������ܣ���L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e�����Ѳ��������շ����������������Ŀռ䡣
 * ����ֵ���ɹ����뷵��OK�����򷵻�ERROR
 **/
status ListInsert(LinkList *L,int i,ElemType e){
    //��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
    //i�ĺϷ�ֵΪ1��i��ListLength+1
    int j;//������
    LinkList temp_L=NULL;//��ʱָ�룬����ָ���i-1��Ԫ��
    LinkList temp_Insert=NULL;//������Ľ��
    if (i<1 || i>ListLength(*L)+1) return ERROR;     //i���Ϸ�

    for(temp_L=(*L),j=0;j<i-1;j++){//�ҵ���i-1�����
        temp_L=temp_L->next;
    }
    temp_Insert = (LinkList)malloc(sizeof(LNode));
    if (temp_Insert==NULL) return OVERFLOW;   //����ռ�ʧ��

    temp_Insert -> data = e;
    temp_Insert -> next = temp_L -> next;
    temp_L -> next = temp_Insert;

    return OK;
}

/**
 * �������ƣ�ListDelete
 * �������������Ա�L�ĵ�ַ��ɾ����λ��i��ָ��e�ĵ�ַ��
 * �������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
 * ����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
 **/
status ListDelete(LinkList *L,int i,ElemType *e)
{
    //ɾ��L�ĵ�i������Ԫ�أ���e������ֵ
    int j;//������

    LinkList temp_L=NULL;//��ʱָ�룬����ָ���i-1��Ԫ��
    LinkList temp_Delete=NULL;//��ʱָ�룬����ָ���ɾ��Ԫ��
    if (i<1 || i>ListLength(*L)) return ERROR;     //i���Ϸ�

    for(temp_L=(*L),j=0;j<i-1;j++){//�ҵ���i-1�����
        temp_L=temp_L->next;
    }
    temp_Delete = temp_L->next;
    (*e)=temp_Delete->data;

    if (temp_L -> next -> next){//�����ɾ��Ԫ�ز������һ��
        temp_L -> next = temp_L -> next -> next;
    }
    else temp_L -> next = NULL;//��ɾ��Ԫ�������һ������ǰһ�����ָ��
    free(temp_Delete);
    return OK;
}

/**
 * �������ƣ�ListTrabverse
 * �������������Ա�L
 * �������ܣ�������ʾ���Ա��е�ÿ��Ԫ�ء�
 * ����ֵ���ɹ������������Ա�ĳ��ȣ����򷵻�ERROR
 **/
status ListTrabverse(LinkList L){
    int i;//������
    printf("\n----------------- all elements ------------------\n");
    for(i=0;i<ListLength(L);) {
        L=L->next;
        printf("%d ",L->data);
    }
    printf("\n---------------------- end ----------------------\n");
    return OK;
}

/**
 * �������ƣ�LoadFile
 * �������������Ա�L���ļ���filename
 * �������ܣ����ļ������ݶ��룬���뵱ǰ���Ա�
 * ����ֵ���ɹ���ȡ����OK�����򷵻�ERROR
 **/
status LoadFile(LinkList L,char filename[20]){
    ElemType elem_read;//��ȡ�ļ�����
    int i=0;//������
    FILE *fp;
    fp = fopen(filename, "r");
    /*���ļ���ʮ�����ַ���ʽԪ�����ΰ�����ϵͳ*/
    while(fscanf(fp,"%d ",&elem_read)!=EOF){
        printf("      �����%d��Ԫ��:%d...\n", ++i , elem_read);
        ListInsert(&L,i,elem_read);//�������������
    }
    fclose(fp);

    if(!i) return ERROR;
    else return OK;
}

/**
 * �������ƣ�SaveAsFile
 * �������������Ա�L���ļ���filename
 * �������ܣ������Ա������ݴ����ļ���
 * ����ֵ�����ɹ�д���򷵻�OK�����򷵻�ERROR
 **/
status SaveAsFile(LinkList L,char filename[20]){
    ElemType elem_read;//��ȡ�ļ�����
    int i;//������
    FILE *fp;
    fp = fopen(filename, "wb+");
    /*������Ԫ�����ΰ�ʮ�����ַ���ʽд���ļ�*/
    LinkList temp_L=L;
    for (i = 1; i <= ListLength(L); i++){
        temp_L = temp_L->next;
        printf("      д���%d��Ԫ��:%d...\n", i , temp_L->data);
        fprintf(fp, "%d ", temp_L->data);
    }
    fclose(fp);
    return OK;
}

/**
 * �������ƣ�MulList
 * �������������Ա�L�ĵ�ַ������ͷM�ĵ�ַ����ǰ�����list_num_cur�����л����ı����list_num
 * �������ܣ��л�������
 * ����ֵ���ɹ��л�����OK�����򷵻�ERROR
 **/
status MulList(LinkList *L,MulNode *M,int list_num_cur,int list_num){
    //�л���������Ŀ����������½�
    MulNode *mul_temp=NULL;//���ڱ������ṹ
    MulNode *mul_new=NULL;//�����½������
    //�洢��
    for(mul_temp=M->next;mul_temp!=NULL;mul_temp=mul_temp->next){//�����ṹ�еĶ�Ӧ�ڵ㸳ֵ����������
        if(mul_temp->list_num==list_num_cur){
            mul_temp->list_head=(*L);
            break;
        }
    }

    //�л���Ϊ��ͷL��ֵ��
    for(mul_temp=M;mul_temp->next!=NULL;mul_temp=mul_temp->next){//��ѯ���ṹ�еĶ�Ӧ�ڵ㣬�л�������
        if(mul_temp->next->list_num==list_num){//����ѯ�ɹ��������
            (*L) = mul_temp->next->list_head;
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

    (*L) = mul_new -> list_head;

    return ERROR;
}
