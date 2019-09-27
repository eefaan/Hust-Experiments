//5.2.1
#include<stdio.h>
void sort(int b[],int n);//
int main(void)
{
    int a[10] = {27, 13, 5, 32, 23, 3, 17, 43, 55, 39};
    //void sort(int [],int);//
    int i;
    sort(a,10);//
    for(i = 0; i < 10; i++)
       printf("%6d",a[i]);
    printf("\n");
    return 0;
}
void sort(int b[], int n)
{
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for ( j = 0; j < n - i - 1; j++)
            if(b[j] > b[j+1])//
                t = b[j], b[j] = b[j+1], b[j+1] = t;
}

//5.2.2(1)
#include<stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M], b[M];
    int i, j, k;
    for(i = 0; i < M; i++)
        a[i] = i + 1;
    for(i = M, j = 0; i > 1; i--)
    {
    for(k = 1; k <= N; k++)
        if(++j > i - 1) j = 0;
    b[M-i] = j?a[j-1]:a[i-1];
    if(j)
        for(k = --j; k < i; k++)
            a[k]=a[k+1];
    }
    for(i = 0; i < M - 1; i++)
        printf("%6d", b[i]);
    printf("%6d\n", a[0]);
}

//5.2.2(2)

#include<stdio.h>
#define M 10
#define N 3
int main(void)
{
    int a[M], b[M];	/* 数组a存放圈中人的编号，数组b存放出圈人的编号 */
    int i, j, k;

    for(i = 0; i < M; i++)			/* 对圈中人按顺序编号1—M */
        a[i] = i + 1;

    for(i = M, j = 0; i > 1; i--)
    {
    /* i表示圈中人个数，初始为M个，剩1个人时结束循环；j表示当前报数人的位置 */
    for(k = 1; k <= N; )			/* 1至N报数 */
        {
            if (++j > M - 1) j = 0;

            if (j)
                {if (a[j-1]!=0) k++;}
            else if(j==0)
                if (a[M-1]!=0) k++;


/*			if (j)
			{
				if (a[j - 1] != 0) k++;
			}
			else if(j==0)
			{
				if (a[M - 1] != 0) k++;
			}*/
        }
    b[M-i] = j?a[j-1]:a[M-1];	/* 将报数为N的人的编号存入数组b */
    if (j) a[j-1] = 0;
    else if (~j) a[M - 1] = 0;
    //if(j)
    //    for(k = --j; k < i; k++)	/* 压缩数组a，使报数为N的人出圈 */
    //        a[k]=a[k+1];
    }

    for(i = 0; i < M - 1; i++)		/* 按次序输出出圈人的编号 */
        printf("%6d", b[i]);

    for(i=0;i<M-1;i++)
        if(a[i]!=0)
            printf("%6d\n", a[i]);			/* 输出圈中最后一个人的编号 */

}

