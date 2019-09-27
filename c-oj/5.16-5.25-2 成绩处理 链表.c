#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct score_tab{
    char id[15];
    char name[20];
    float score_en;
    float score_math;
    float score_phy;
    float score_c;
    float score_sum;
    float score_avg;
    struct score_tab *next;
}studs;

studs *head=NULL;

void exchange(char id[15],char subname[20],float grade)
{
    studs *tail;
    tail=head;
    while(tail){
        if (!strcmp(tail->id,id)) break;
        tail=tail->next;
    }
    if(!strcmp(subname,"English")) tail->score_en=grade;
    else if(!strcmp(subname,"Math")) tail->score_math=grade;
    else if(!strcmp(subname,"Physics")) tail->score_phy=grade;
    else if(!strcmp(subname,"C")) tail->score_c=grade;
}

void sort_list_data(studs *head)
{
    studs *p1=head,*p2;
    int len=0,i,j;
    char char_temp[20];
    float temp;
    while(p1){
        len++;
        p1=p1->next;
    }

    for(i=0,p1=head ; i<len-1 ; i++,p1=p1->next)
        for(j=i+1,p2=p1->next ; j<len ; j++,p2=p2->next)
            if(p1->score_avg>p2->score_avg){
        //id
        strcpy(char_temp,p1->id);
        strcpy(p1->id,p2->id);
        strcpy(p2->id,char_temp);
        //name
        strcpy(char_temp,p1->name);
        strcpy(p1->name,p2->name);
        strcpy(p2->name,char_temp);
        //avg
        temp=p1->score_avg;
        p1->score_avg=p2->score_avg;
        p2->score_avg=temp;
        //sum
        temp=p1->score_sum;
        p1->score_sum=p2->score_sum;
        p2->score_sum=temp;
        //en
        temp=p1->score_en;
        p1->score_en=p2->score_en;
        p2->score_en=temp;
        //math
        temp=p1->score_math;
        p1->score_math=p2->score_math;
        p2->score_math=temp;
        //phy
        temp=p1->score_phy;
        p1->score_phy=p2->score_phy;
        p2->score_phy=temp;
        //c
        temp=p1->score_c;
        p1->score_c=p2->score_c;
        p2->score_c=temp;
    }
}

void sort_list_point_v1(studs **head)//choose_head_alone
{
    studs *prior1,*prior2,*p1,*p2,*t;
    int i=0;
    p1=*head;
    for(p2=p1->next,prior2=p1 ; p2!=NULL ; prior2=p2,p2=p2->next)
        if(p1->score_avg>p2->score_avg){
            prior2->next=p1;
            t=p1->next;
            p1->next=p2->next;
            (*head)=p2;
            p2->next=t;
            p1=p2;
        }
    for(prior1=*head,p1=prior1->next ; p1->next!=NULL ; prior1=p1,p1=p1->next)
        for(p2=p1->next,prior2=p1 ; p2!=NULL ; prior2=p2,p2=p2->next)
            if(p1->score_avg>p2->score_avg){
                t=p2->next;
                prior1->next=p2;
                prior2->next=p1;
                p2->next=p1->next;
                p1->next=t;
                p1=p2;
            }
}

void sort_list_point_v2(studs **head)//add_a_point
{
    studs *prior1,*prior2,*p1,*p2,*t;
    int i=0;
}

int main (void)
{
    int N,i,j;
    scanf("%d",&N);
    studs *tail;
    head=(studs*)malloc(sizeof(studs));

    //input
    scanf("%s%s%f%f%f%f", head->id, head->name, &head->score_en, &head->score_math, &head->score_phy, &head->score_c);
    tail=head;
    for(i=1;i<N;i++){
        tail->next=(studs*)malloc(sizeof(studs));
        tail=tail->next;
        scanf("%s%s%f%f%f%f", tail->id, tail->name, &tail->score_en, &tail->score_math, &tail->score_phy, &tail->score_c);
    }
    tail->next=NULL;

    //output_first
    printf("ID             Name                English   Math      Physics   C         \n");
    tail=head;
    while(tail){ //or for(i=0;i<N;i++)
        printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",tail->id, tail->name, tail->score_en, tail->score_math, tail->score_phy, tail->score_c);
        tail=tail->next;
    }
    printf("\n");

    //exchange_the_tab
    int change_num;
    char change_id[15];
    char change_subname[10];
    float change_grade;
    scanf("%d",&change_num);
    while(change_num--){
        scanf("%s%s%f",change_id,change_subname,&change_grade);
        exchange(change_id,change_subname,change_grade);
    }
    //output_after_exchange
    printf("Alter:\nID             Name                English   Math      Physics   C         \n");
    tail=head;
    while(tail){
        printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",tail->id, tail->name, tail->score_en, tail->score_math, tail->score_phy, tail->score_c);
        tail=tail->next;
    }
    printf("\n");

    //calculate_sum_and_avg
    float sum,avg;
    tail=head;
    while(tail){
        tail->score_sum=(tail->score_en+tail->score_math+tail->score_phy+tail->score_c);
        tail->score_avg=tail->score_sum/4;
        tail=tail->next;
    }
    //output_after_cal
    printf("SumAndAvg:\nID             Name                SUM       AVG       \n");
    tail=head;
    while(tail){
        printf("%-15s%-20s%-10.2f%-10.2f\n",tail->id, tail->name, tail->score_sum, tail->score_avg);
        tail=tail->next;
    }
    printf("\n");

    //Sort
    /**************change data***************/
    sort_list_data(&head);
    /**************change point**************/
    //sort_list_point_v1(&head);
    //sort_list_point_v2(&head);
    //output_after_sort
    printf("Sort:\nID             Name                AVG       \n");
    tail=head;
    while(tail){
        printf("%-15s%-20s%-10.2f\n",tail->id, tail->name, tail->score_avg);
        tail=tail->next;
    }
    printf("\n");
}
