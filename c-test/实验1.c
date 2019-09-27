#include<stdio.h>
void main( )
/*{
   int a, b, t;
   printf(¡°Input two integers:¡±);
   scanf(¡°%d %d¡±,&a,&b);
   t=a, a=b, b=t;
   prinf(¡°\na=%d,b=%d¡±,a,b);
}*/


{

int a,b;
printf("Input two integers:");
scanf("%d %d",&a,&b);
a=a+b;
b=a-b;
a=a-b;
printf("\na=%d,b=%d",a,b);


}
