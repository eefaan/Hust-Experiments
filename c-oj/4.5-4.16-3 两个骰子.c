#include<stdio.h>
int minesum(int i)//各位数求和
{
	while (i == 0)
	{
		return 0;
	}

	int n, mask = 1;
	for (n = 0;i / mask != 0;mask *= 10)
	{
		n += (i % (mask * 10) / mask);
	}
	return n;
}

int dice_1to6(int i)//启动数→骰子数1~6
{
	int n;
	for (n = 1;i>0;i--)
	{
		if (n != 6)
		{
			n += 1;
		}
		else
		{
			n = 1;
		}
	}
	return n;
}

int game(int a, int b)//a,b为启动数
{
	int A, B, dice1, dice2, flag, sumdice;
	int n;//轮数

	for (n = 1;; n++ )
	{
		/*
		A = a + n - 1;
		B = b + n - 1;

		A = minesum(A);
		B = minesum(B);//启动→sum步数

		dice1 = dice_1to6(A);
		dice2 = dice_1to6(B);//sum→骰子数

		sumdice = dice1 + dice2;//两骰子数之和
		*/

		sumdice= dice_1to6(minesum(a + n - 1)) + dice_1to6(minesum(b + n - 1)) ;//两骰子数之和

		if (n == 1)
		{
			if (sumdice == 7 || sumdice == 11)
			{
				return 1;
			}
			else if (sumdice == 2 || sumdice == 3 || sumdice == 12)
			{
				return 0;
			}

			flag = sumdice;
		}

		else if (n>1)
			{
				if (sumdice == flag)
				{
					return 1;
				}
				else if (sumdice == 7)
				{
					return 0;
				}
			}
	}
}

int main()
{
	int N, a, b;
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d%d", &a, &b);
		if (a >= 0 && b >= 0 && a <= 10000 && b <= 10000)
		{
			/*int state;
			state=game(a,b);
			switch(state)
			{
			case 1:printf("success!\n");
			case 0:printf("fail!\n");
			}*/

			if (game(a, b) == 1)
			{
				printf("success!\n");
			}
			else if (game(a, b) == 0)
			{
				printf("fail!\n");
			}
		}
		else
		{
			printf("wrong input!\n");
		}
	}
	return 0;
}

