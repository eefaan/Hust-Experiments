#include<stdio.h>
int main(void)
{
    int i,a[100]={0,1,1};
    for (i=3;i<100 && i>2;i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}
    //定义数列

    int n,m;
    while(1)
    {
        scanf("%d",&n);

        if(n==0)
        {
            return 0;
        }

        else if(n>0&&n<3)
        {
            printf("Error!\n\n");
        }

        else if(n>2)
        {
            for(m=1;m<=n;m++)
            {
                printf("%10d",a[m]);
                if(m%8==0)
                {
                    printf("\n");
                }
            }
            if(n%8!=0){printf("\n\n");}
            else{printf("\n");}
        }
    }
}
