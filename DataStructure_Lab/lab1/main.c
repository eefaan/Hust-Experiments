#include "LinearTable.h"

void main(void){
    SqList MulList[MAX];//���
    int temp;
    for(temp=0;temp<MAX;temp++){//��ʼ��elemΪnull
        MulList[temp].elem=NULL;
    }
    SqList *L;//��ǰ��
    int list_num=0;
    L=MulList+list_num;//ָ���1

    int op=1;
    int length;//���Ա���
    int i;//λ��
    int e;//����λ��i��ֵe
    int cur;//��ҪѰ��ǰ�����̵�����
    int pre_e;//����ǰ��
    int next_e;//���غ��
    ElemType elem_read;//��ȡ�ļ�����
    FILE *fp;
    char filename[20];

    while(op){

        fflush(stdin);
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("      ��ǰ�����ı����Ϊ%d\n",list_num+1);
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
            if(IntiaList(L)==OK) printf("      ���Ա����ɹ���\n");
            else printf("      ���Ա��Ѵ��ڻ�洢�ռ䲻�㣬����ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 2:
            //printf("\n----DestroyList���ܴ�ʵ�֣�\n");
            if(DestroyList(L)==OK) printf("      ���Ա����ٳɹ���\n");
            else printf("      ���Ա����ڣ�����ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 3:
            //printf("\n----ClearList���ܴ�ʵ�֣�\n");
            if(ClearList(L)==OK) printf("      ���Ա��ÿճɹ���\n");
            else printf("      ���Ա����ڻ����Ա���Ϊ�գ��ÿ�ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 4:
            //printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else if(ListEmpty(*L)==OK) printf("      ���Ա�Ϊ�գ�\n");
            else printf("      ���Ա�Ϊ�գ�\n");
            getchar();getchar();
            break;
        case 5:
            //printf("\n----ListLength���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                length=ListLength(L);
                printf("      ���Ա���Ϊ%d��\n",length);
            }
            getchar();getchar();
            break;
        case 6:
            //printf("\n----GetElem���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ������λ�򣬽�Ϊ�����ظ�λ������Ԫ�ص�ֵ\n\n");
                printf("      λ��");
                scanf("%d",&i);
                if(GetElem(*L,i,&e)==OK) printf("      ���Ա��е�%d������Ԫ�ص�ֵΪ%d\n",i,e);
                else printf("      ����Խ�磬��λ�򲻴��ڣ�\n");
            }
            getchar();getchar();
            break;
        case 7:
            //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ����ݵ�λ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&e);
                if(LocateElem(*L,e,&i)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�ص�λ��Ϊ%d\n",e,i);
                else printf("      ���Ա���δ��ѯ��������Ԫ�أ�\n");
            }
            getchar();getchar();
            break;
        case 8:
            //printf("\n----PriorElem���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ�����Ԫ�ص�ǰ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&cur);
                if(PriorElem(*L,cur, &pre_e)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�ص�ǰ��Ϊ%d��\n",cur,pre_e);
                else printf("      ���Ա���δ��ѯ��������Ԫ�ػ������Ԫ����ǰ����\n");
            }
            getchar();getchar();
            break;
        case 9:
            //printf("\n----NextElem���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ����������Ԫ�ص�ֵ����Ϊ�����ظ�����Ԫ�صĺ��\n\n");
                printf("      ����Ԫ�ص�ֵ��");
                scanf("%d",&cur);
                if(NextElem(*L,cur, &next_e)==OK) printf("      ���Ա���ֵΪ%d������Ԫ�صĺ��Ϊ%d��\n",cur,next_e);
                else printf("      ���Ա���δ��ѯ��������Ԫ�ػ������Ԫ���޺�̣�\n");
            }
            getchar();getchar();
            break;
        case 10:
            //printf("\n----ListInsert���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ��Ҫ��������Ԫ�أ������뽫Ҫ���������Ԫ�ص�λ����ֵ\n\n");
                printf("      λ��");
                scanf("%d",&i);
                printf("      ֵ��");
                scanf("%d",&e);
                if(ListInsert(L,i,e)==OK) printf("      ����Ԫ�ز���ɹ���\n");
                else printf("      Խ�磬����Ԫ�ز���ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 11:
            //printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else{
                printf("      ��Ҫɾ������Ԫ�أ������뽫Ҫɾ��������Ԫ�ص�λ��\n\n");
                printf("      λ��");
                scanf("%d",&i);
                if(ListDelete(L,i,&e)==OK) printf("      ����Ԫ��ɾ���ɹ���ɾ����Ԫ��Ϊ%d��\n",e);
                else printf("      Խ�磬����Ԫ��ɾ��ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
            if(!L->elem) printf("      ���Ա�δ������\n");//������
            else if(!ListTrabverse(*L)) printf("      ���Ա��ǿձ�\n");
            getchar();getchar();
            break;
        case 13:
            //printf("\n----��ȡ�ļ����ܴ�ʵ�֣�\n");
            if(!L->elem){
                printf("      ���Ա�δ������\n");//������
                getchar();getchar();
            }
            else{
                printf("      �����ļ��ж�ȡ���ݲ����뵱ǰ���Ա����.\n      ������Ҫ��ȡ���ļ���: ");
                getchar();
                gets(filename);
                fp = fopen(filename, "r");
                i=0;
                /*���ļ���ʮ�����ַ���ʽԪ�����ΰ�����ϵͳ*/
                while(fscanf(fp,"%d ",&elem_read)!=EOF){
                    printf("      �����%d��Ԫ��:%d...\n", ++i , elem_read);
                    ListInsert(L,i,elem_read);//�������������
                }
                if(!i) printf("      �ļ���ȡʧ�ܣ��ļ������ڻ�����������\n");
                else printf("      �ļ���ȡ�ɹ�����Ϊ%d.\n",L->length);
                fclose(fp);getchar();
            }
            break;
        case 14:
            //printf("\n----����ļ����ܴ�ʵ�֣�\n");
            if(!L->elem){
                printf("      ���Ա�δ������\n");//������
                getchar();getchar();
            }
            else{
                printf("      ������Ҫд����ļ���: ");
                getchar();
                gets(filename);
                fp = fopen(filename, "wb+");
                /*������Ԫ�����ΰ�ʮ�����ַ���ʽд���ļ�*/
                for (i = 1; i <= L->length; i++){
                    printf("      д���%d��Ԫ��:%d...\n", i , L->elem[i]);
                    fprintf(fp, "%d ", L->elem[i]);
                }
                printf("      �ļ�д��ɹ�.\n");
                fclose(fp);getchar();
            }
            break;
        case 15:
            //printf("\n----������ܴ�ʵ�֣�\n");
            printf("      ������Ҫ�л����ı����[1~%d]��",MAX);
            scanf("%d",&list_num);
            if(--list_num<0 || list_num>MAX-1){
                printf("\n      ��Ӧ�����ڣ��л�Ϊ��1\n");
                list_num=0;
                getchar();getchar();
                break;
            }
            else printf("\n      �������л��ɹ���\n");
            L=MulList+list_num;
            getchar();getchar();
            break;
        case 0:
            break;
        }//end of switch

    }//end of while

    printf("\n    ��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

/**
 * �������ƣ�InitiaList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ�����һ���յ����Ա�
 * ����ֵ���ɹ����췵��OK�����򷵻�ERROR
 **/
status IntiaList(SqList *L){
    //����һ��������
    if(L->elem) return ERROR;       //���ѱ���ʼ��
	L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) return ERROR;      //�洢����ʧ��
	L->length=0;                    //�ձ���Ϊ0
    L->listsize=LIST_INIT_SIZE;     //��ʼ�洢����
	return OK;
}

/**
 * �������ƣ�DestroyList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ�ɾ�����Ա�
 * ����ֵ���ɹ����ٷ���OK�����򷵻�ERROR
 **/
status DestroyList(SqList *L){
    //�������Ա�
    if(!L->elem) return ERROR;//������
    free(L->elem);
    L->elem=NULL;
    return OK;
}

/**
 * �������ƣ�ClearList
 * �������������Ա�L�ĵ�ַ
 * �������ܣ��������Ա�
 * ����ֵ���ɹ��ÿշ���OK�����򷵻�ERROR
 **/
status ClearList(SqList *L){
    //��L����Ϊ�ձ�
    if(!L->elem) return ERROR;//������
    if(L->length==0) return ERROR;//���Ա���Ϊ��
    L->elem=NULL;
    IntiaList(L);
    return OK;
}

/**
 * �������ƣ�ListEmpty
 * �������������Ա�L
 * �������ܣ��ж����Ա��Ƿ�Ϊ��
 * ����ֵ����LΪ�ձ��򷵻�OK�����򷵻�ERROR
 **/
status ListEmpty(SqList L){
    //�ж�L�Ƿ�Ϊ�ձ����򷵻�OK�����򷵻�ERROR
    if(L.length == 0) return OK;
    else return ERROR;
}

/**
 * �������ƣ�ListLength
 * �������������Ա�L�ĵ�ַ
 * �������ܣ��������Ա�L������Ԫ�ظ�����
 * ����ֵ���ɹ�����L������Ԫ�ظ�����ʧ�ܷ���ERROR
 **/
int ListLength(SqList *L){
    //����˳�����Ա���
    if(L) return L->length;
    return ERROR;
}

/**
 * �������ƣ�GetElem
 * �������������Ա�L����i�����ݣ�eΪ��i�����ݣ�
 * �������ܣ����Ҳ���e����L�е�i��Ԫ�ص�ֵ��
 * ����ֵ���ɹ��򷵻�OK�����򷵻�ERROR
 **/
status GetElem(SqList L,int i,ElemType *e){
    //��e����L�е�i������Ԫ�ص�ֵ
    if(i<1 || i>L.length) return ERROR;//Խ��
    else (*e)=L.elem[i];
    return OK;
}

/**
 * �������ƣ�LocateElem
 * �������������Ա�L����i�����ݣ�eΪ��i�����ݣ�
 * �������ܣ�����L����e��ͬ�������ڵ�λ����i���ظ�λ��
 * ����ֵ���ɹ��򷵻�OK���������򷵻�ERROR
 **/
status LocateElem(SqList L,ElemType e,ElemType *i){//�򻯹�
    //���Ա�L�Ѵ��ڣ���i����L�е�һ��e��λ����������e�����ڣ�����ERROR
    int temp;

    for(temp=1;temp<=L.length;temp++){
        if(L.elem[temp]==e){
            (*i)=temp;
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
status PriorElem(SqList L,ElemType cur,ElemType *pre_e){
    //�����Ա�L�Ѵ���
    //��cur��L������Ԫ���Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre.e�޶���
    int cur_e;//λ��

    if(LocateElem(L,cur,&cur_e)==OK){
        if(cur_e!=1){
            (*pre_e) = L.elem[cur_e-1];
            return OK;
        }
    }

    return ERROR;
}

/**
 * �������ƣ�NextElem
 * �������������Ա�L�����ҵ�����cur,���next_e��
 * �������ܣ�����L����cur��ͬ�ĵ�һ�����ݣ�����next_e��������
 * ����ֵ���ɹ��򷵻�OK�����޺���Լ���������򷵻�ERROR
 **/
status NextElem(SqList L,ElemType cur,ElemType *next_e){
    //�����Ա�L�Ѵ���
    //��cur��L������Ԫ���Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next.e�޶���
    int cur_e;//λ��

    if(LocateElem(L,cur,&cur_e)){
        if(cur_e!=L.length){
            (*next_e) = L.elem[cur_e+1];
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
status ListInsert(SqList *L,int i,ElemType e){
    //��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
    int j;
    //i�ĺϷ�ֵΪ1��i��ListLength+1
    if (i<1 || i>L->length+1) return ERROR;     //i���Ϸ�
    if (L->length >= L->listsize){    //���������洢�ռ�
        ElemType *newbase = (ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if (newbase==NULL) return OVERFLOW;   //����ռ�ʧ��
        L->elem = newbase;
        L->listsize += LISTINCREMENT; // ���ӹ̶���С�洢����
	 }
    //����ƶ�Ԫ�أ��ճ���i��Ԫ�صķ���elem[i-1]
    for(j=L->length;j>=i;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i]=e;      /*��Ԫ�ز���*/  //j+1
    L->length++;         /*���Ա��ȼ�1*/
    return OK;
}

/**
 * �������ƣ�ListDelete
 * �������������Ա�L�ĵ�ַ��ɾ����λ��i��ָ��e�ĵ�ַ��
 * �������ܣ�ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
 * ����ֵ���ɹ�ɾ������OK�����򷵻�ERROR
 **/
status ListDelete(SqList *L,int i,ElemType *e)
{
    //ɾ��L�ĵ�i������Ԫ�أ���e������ֵ
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
 * �������ƣ�ListTrabverse
 * �������������Ա�L
 * �������ܣ�������ʾ���Ա��е�ÿ��Ԫ�ء�
 * ����ֵ���ɹ������������Ա�ĳ��ȣ����򷵻�ERROR
 **/
status ListTrabverse(SqList L){
   int i;
   printf("\n----------------- all elements ------------------\n");
   for(i=1;i<=L.length;i++) printf("%d ",L.elem[i]);
   printf("\n---------------------- end ----------------------\n");
   return L.length;
}
