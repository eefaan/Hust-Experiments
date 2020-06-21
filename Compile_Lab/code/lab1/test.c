// example program
int i,j;
int fun(int a, float b)
{
	int m;
	int d;
	d += ( 12 + 6 );
	if (a>b) m=a;
	else m=b;
	return 0;
}
float x,y;

/* Q:
	数据类型至少包括char类型、int类型和float类型
	基本运算至少包括算术运算、比较运算、逻辑运算、自增自减运算和复合赋值运算
	控制语句至少包括if语句和while语句
	其它选项：数组、结构，for循环等等
*/
// my comment test 1
/* my comment test 2 */

char a_char;
int b_int;
float c_float;
void my_func(char a, int b, float c){
	// local var assign
	int test = 10;
	int x,y,z;
	// 算术运算
	x=y+z;
	x=a+b/c*z;
	x=b/c*z+a;


	if(x&&y){
		x++;
		++x;

		x+y++;// equal x+(y++)
		++x+y;// equal (++x)+y
		x+++y;
	}
	else{
		int test_assign = b+x-x/y*z;
	}
	while(x||y){
		y--;
		--y;
	}

	return 's';
	return '\n';
	return 'sss';
}
int z,s;
