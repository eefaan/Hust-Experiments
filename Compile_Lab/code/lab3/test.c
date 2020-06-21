// int i,j;
//
// int fun(int x, int y){
// 	int z;
// 	z = x + 3;
// 	return z;
// }
//
// int main(){
// 	int x = fun(1,2);
// 	return x;
// }


// int fibo(int a){
// 	if(a == 1 || a == 2) return 1;
// 	return fibo(a - 1) + fibo(a - 2);
// }
// int main(){
// 	int m,n,i;
// 	// m = read();
// 	m = 10;
// 	i = 1;
// 	while(i<=m){
// 		n = fibo(i);
// 		// write(n);
// 		i = i + 1;
// 	}
// 	return 1;
// }


int fibo(int a)
{
    int add_1,add_2,sum;
    if(a == 0 || a == 1)
        return 1;
    add_2 = 1;
    sum = 1;
    a = a - 1;
    while(a)
    {
        add_1 = add_2;
        add_2 = sum;
        sum = add_1 + add_2;
        a = a - 1;
    }
    return sum;
}
int main()
{
    int i = 0, n;
	while(i != 9){
		n = fibo(i);
		i = i + 1;
	}
    return i;
}
