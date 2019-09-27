#include<stdio.h>
#define M 5//sub
#define N 5//stu

void ave_stu (double a[N][M]);
void ave_sub (double a[N][M]);
void low_than_ave (double a[N][M]);//each sub
void count_fail_and_perfect (double a[N][M]);

double stu_ave[N]   ,sub_ave[M]   ; int stu_lower[M]   ,stu_fail[M]   ,stu_perfect[M];
double *p1=stu_ave  ,*p2=sub_ave  ; int *p3=stu_lower  ,*p4=stu_fail  ,*p5=stu_perfect;

int main(void)
{
    char sub_name[M][100],stu_name[N][100];
    double stu_grade[N][M];

    int i,j;

    //input subject
    for(i=0;i<M;i++)
        scanf("%s",sub_name[i]);

    //input stu_name and grades
    for(i=0;i<N;i++)
    {
        scanf("%s",stu_name[i]);
        for(j=0;j<M;j++)
            scanf("%lf",&stu_grade[i][j]);
    }

    //main
    ave_stu (stu_grade);
    ave_sub (stu_grade);
    low_than_ave (stu_grade);
    count_fail_and_perfect (stu_grade);

    //output
    for(i=0;i<N;i++)
        printf("Average score of %s is %.2f\n",stu_name[i],*(p1+i));
    for(i=0;i<M;i++)
        printf("Average score of %s is %.2f\n",sub_name[i],*(p2+i));
    for(i=0;i<M;i++)
        printf("Number of students lower than avg of %s is %d\n",sub_name[i],*(p3+i));
    for(i=0;i<M;i++)
        printf("Number of students %s fail is %d\n",sub_name[i],*(p4+i));
    for(i=0;i<M;i++)
        printf("Number of students %s perfect is %d\n",sub_name[i],*(p5+i));
}

void ave_stu (double a[N][M])//*a=stu_grade
{
    int i,j;
    double sum;

    for(i=0;i<N;i++)
    {
        sum=0;
        for(j=0;j<M;j++)
            sum += *(*(a+i)+j);
        *(p1+i)=sum/M;
    }
}

void ave_sub (double a[N][M])//*a=stu_grade
{
    int i,j;
    double sum;

    for(i=0;i<M;i++)
    {
        sum=0;
        for(j=0;j<N;j++)
            sum += *(*(a+j)+i);
        *(p2+i)=sum/N;
    }
}

void low_than_ave (double a[N][M])//each sub
{
    int count,i,j;

    for(i=0;i<M;i++)
    {
        count=0;
        for(j=0;j<N;j++)
            if(*(*(a+j)+i)<*(p2+i)) count++;
        *(p3+i)=count;
    }
}

void count_fail_and_perfect (double a[N][M])
{
    int count1,count2,i,j;

    for(i=0;i<M;i++)
    {
        count1=0;
        count2=0;
        for(j=0;j<N;j++)
        {
            if(*(*(a+j)+i)<60.00) count1++;
            if(*(*(a+j)+i)>=90.00) count2++;
        }
        *(p4+i)=count1;
        *(p5+i)=count2;
    }
}
