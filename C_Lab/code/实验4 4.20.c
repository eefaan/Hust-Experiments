//4.2.1
#include "stdio.h"
#define SUM (a+b)//
#define DIF (a-b)//
#define SWAP(a,b)  a=a+b,b=a-b,a=a-b//
void main()//
{
    int b, a;//
    printf("Input two integers a, b:");
    scanf("%d%d", &a,&b);//
    printf("\nSUM=%d\n the difference between square of a and square of b is:%d",SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d,b=%d\n",a,b);//
}

//4.2.2(1)
#include<stdio.h>//
int max(int x, int y, int z);//
float sum(float x, float y);//

void main(void)
{
  int a, b, c;
  float d, e;
  printf("Enter three integers:");
  scanf("%d%d%d",&a,&b,&c);//
  printf("\nthe maximum of them is %d\n",max(a,b,c));

printf("Enter two floating point numbers:");
scanf("%f%f",&d,&e);//
printf("\nthe sum of them is  %f\n",sum(d,e));
}

int max(int x, int y, int z)
{
   int t;
   if (x>y)
     t=x;
   else
     t=y;
   if (t<z)
     t=z;
   return t;
}

float sum(float x, float y)
{
  return (x+y);
}

//4.2.2(2)
#include<stdio.h>
#define max(a,b,c) a>=b?(a>=c)?a:c:(b>=c)?b:c
float sum(float,float);
void main(void)
{
  int a, b, c;
  float d, e;
  printf("Enter three integers:");
  scanf("%d%d%d",&a,&b,&c);
  printf("\nthe maximum of them is %d\n",max(a,b,c));
printf("Enter two floating point numbers:");
scanf("%f%f",&d,&e);//
printf("\nthe sum of them is  %f\n",sum(d,e));
}
float sum(float x, float y)
{
  return x+y;
}


//4.2.3
#include<stdio.h>
#include<assert.h>
#define  R
int integer_fraction(float x);
void  main(void)
{
float  r, s;
int s_integer=0;
    printf ("input a number: ");
    scanf("%f",&r);
    #ifdef  R
       s=3.14159*r*r;
       printf("area of round is: %f\n",s);
       s_integer= integer_fraction(s);
       printf("the integer fraction of area is %d\n", s_integer);
       assert((s-s_integer)<1.0);
    #endif
}

int integer_fraction(float x)
{
  int i=x;
  return i;
}

//4.2.4(1)
#include<stdio.h>
#include<math.h>
#define S(a,b,c) (a+b+c)/2
#define AREA(a,b,c) sqrt(S(a,b,c)*(S(a,b,c)-a)*(S(a,b,c)-b)*(S(a,b,c)-c))

int main(void)
{
    double a,b,c;
    while(scanf("%lf%lf%lf",&a,&b,&c)!=EOF)
    {
        getchar();
        printf("%.0lf %lf\n",S(a,b,c),AREA(a,b,c));
    }
}

//4.2.4(2)
