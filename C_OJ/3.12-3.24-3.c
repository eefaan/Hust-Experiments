#include<stdio.h>

enum month
{
	jan,feb,mar,apr,
	may,june,july,aug,
	sept,oct,nov,dec
};

int main()
{
int year;
enum month day; 
char *monthDay[] = 
{
	"January,31","February,28","March,31","April,30",
	"May,31","June,30","July,31","August,31",
	"September,30","October,31","November,30","December,31"
};

scanf("%d", &year);
if ( (year%4==0&&year%100!=0) || (year%400==0) )
{
	monthDay[1]="February,29";
}

for(day=jan; day<=dec; day++)
{
	printf("%s\n",monthDay[day]);
}

return 0;
}
 
