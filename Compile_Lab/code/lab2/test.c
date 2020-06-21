int i,j;
// 1.重复定义
int i,j;
int fun(int a, float b)
{
	int m;
	if (a>b) m=a;
	else m=b;

	return m;
}

// 2.函数名重复
int fun(){}
// 3.参数定义重复
int fun2(int a, float a){}

int fun3(int myint, float myfloat)
{
	int i;
	int a,b,c;
	float x,y,z;
	fun(a,x);
	// 4.参数类型不符
	fun(a,b);
	// 5.参数太多
	fun(a,x,c);
	// 6.参数太少
	fun(b);
	// 7.变量未定义
	p = 10;
	// 8.函数名，类型不匹配
	fun = 10;
	x = fun;
	// 9.赋值语句需要左值
	10 = i;
	// 10.函数未定义
	fun4(x);
	// 11.x不是函数
	x(y);
	// 12.返回值类型错误
	return 2.0;
	return 0;
}

int fun4(){
	int x;
	// 13.continue error
	continue;
	while(1){
		continue;
		break;
	}
	// 14.break error
	break;
	// 15.++/--
	(x+y)++;
	++(x+y);
	(x+y)--;
	--(x+y);

	return 0;
}

float x,y;
