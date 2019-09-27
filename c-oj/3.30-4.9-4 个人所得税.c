#include<stdio.h>
int main (void)
{
    double n,tax;
    while(scanf("%lf",&n)!=EOF)
    {
		if (n>0)
		{
        	if(n>0&&n<=1000)
        	{
        	    tax = 0;
        	}
        	else if(n>1000&&n<=2000)
        	{
        	    tax = (n-1000)*0.05;
        	}
        	else if(n>2000&&n<=3000)
        	{
        	    tax = (n-2000)*0.1 +50;
        	}
        	else if(n>3000&&n<=4000)
        	{
        	    tax = (n-3000)*0.15+150;
        	}
        	else if(n>4000&&n<=5000)
        	{
        	    tax = (n-4000)*0.2 +300;
        	}
        	else if(n>5000)
        	{
        	    tax = (n-5000)*0.25 +500;
        	}
        	printf("%lf\n",tax);
		}
		else
        {
			printf("wrong!\n"); 
			return 0;
		} 
    }
}
