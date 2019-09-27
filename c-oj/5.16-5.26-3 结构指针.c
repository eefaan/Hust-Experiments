#include<stdio.h>

struct Student {
	int num;
	char name[19];
	double score;
};

int main(void)
{
	int N, i;
	struct Student stu[3];
	struct Student* p;
	p = stu;

	scanf("%d", &N);
	while (N--)
	{
		//input
		for (i = 0;i<3;i++)
			scanf("%d%s%lf", &stu[i].num, stu[i].name, &stu[i].score);

		//output without point
		for (i = 0;i<3;i++)
			printf("%d\t%-20s%f\n", stu[i].num, stu[i].name, stu[i].score);

		//output with point
		for (i = 0;i<3;i++)
			printf("%d\t%-20s%f\n", (p+i)->num, (p+i)->name, (p+i)->score);

	}
}
