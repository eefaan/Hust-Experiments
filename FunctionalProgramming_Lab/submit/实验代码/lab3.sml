"----------------------- Question 1 -----------------------";
(*** 1 ***)
(*编写函数thenAddOne，要求：*)
(*函数类型为: ((int ->int) * int) -> int；*)
(*功能为将一个整数通过函数变换(如翻倍、求平方或求阶乘)后再加1。*)
fun double (0 : int) : int = 0
	| double n = 2 + double (n - 1);
fun square (0 : int) : int = 0
	| square n = if n > 0 then square(n-1) + double(n-1) + 1 else square(~n);
fun thenAddOne(f:int->int, x:int) = f(x) + 1;

thenAddOne(double, 10);
thenAddOne(square, 10);

"----------------------- Question 2 -----------------------";
(*** 2 ***)
(*编写函数mapList，要求：*)
(*函数类型为: ((‘a -> ‘b) * ‘a list) -> ‘b list；*)
(*功能为实现整数集的数学变换(如翻倍、求平方或求阶乘)。*)
fun mapList(f:'a->'b, []:'a list) : 'b list = []
	| mapList(f:'a->'b, x::L:'a list) : 'b list = f(x) :: mapList(f, L);

mapList(double, [1,3,5]);
mapList(square, [1,3,5]);
(*fun doubleList ([] : int list) : int list = []
	| doubleList (x::L : int list) : int list = double(x) :: doubleList(L);
fun squareList ([] : int list) : int list = []
	| squareList (x::L : int list) : int list = square(x) :: squareList(L);
doubleList [1,3,5];
squareList [1,3,5];*)


"----------------------- Question 3 -----------------------";
(*** 3 ***)
(*编写函数mapList’，要求：*)
(*函数类型为: (‘a -> ‘b) -> (‘a list -> ‘b list)；*)
(*功能为实现整数集的数学变换(如翻倍、求平方或求阶乘)。*)
(*比较函数mapList’和mapList，分析、体会它们有什么不同。*)
fun mapList' (f : 'a -> 'b) ([] : 'a list) : 'b list = []
	| mapList' (f : 'a -> 'b) (L : 'a list) : 'b list = mapList(f, L);

(mapList'(double)) ([1,3,5]);
(mapList'(square)) ([1,3,5]);


"----------------------- Question 4 -----------------------";
(*** 4 ***)
(*编写函数findOdd，要求：*)
(*函数类型为: int list -> int option；*)
(*功能为：如果x为L中的第一个奇数，则返回SOME x；否则返回NONE*)
fun oddP (0 : int) : bool = false
	| oddP 1 = true
	| oddP n = if n > 0 then oddP (n - 2) else oddP(~n);
fun findOdd ([] : int list) : int option = NONE
	| findOdd (x::L : int list) : int option = if oddP(x) then SOME(x) else findOdd(L);

findOdd [2,4,6,8,1,3,5];
findOdd [2,4,6,8];


"----------------------- Question 5 -----------------------";
(*** 5 ***)
(*编写函数subsetSumOption: int list * int -> int list option，要求：*)
(*对函数subsetSumOption(L, s)：如果L中存在子集L’，满足其中所有元素之和为s，则结果为SOME L’；否则结果为NONE。*)
fun subsetSumOption (L : int list, 0 : int) : int list option = SOME([])
	| subsetSumOption ([] : int list, s : int) : int list option = NONE
	| subsetSumOption (x::L : int list, s : int) : int list option =
	case subsetSumOption (L, s-x) of
		NONE => subsetSumOption(L, s)
		| SOME(l) => SOME(x::l);

subsetSumOption ([1,3,5,7],4);
subsetSumOption ([1,3,5,7],12);


"----------------------- Question 6 -----------------------";
(*** 6 ***)
(*编写函数：*)
(*exists: (‘a -> bool) -> ‘a list -> bool*)
(*forall: (‘a -> bool) -> ‘a list -> bool*)
(*对函数p: t -> bool, 整数集L: t list,
有： exist p L =>* true if there is an x in L such that p x=true;
	exits p L =>* false otherwise.
	forall p L =>* true if p x = true for every item x in L;
	forall p L =>* false otherwise.*)
fun exists (f : 'a -> bool) ([] : 'a list) : bool = false
	| exists (f : 'a -> bool) (x::L : 'a list) : bool =
	case f(x) of
		false => exists(f)(L)
		| true => true;

(exists(oddP)) ([2,4,6]);
(exists(oddP)) ([2,4,6,1]);

fun forall (f : 'a -> bool) ([] : 'a list) : bool = true
	| forall (f : 'a -> bool) (x::L : 'a list) : bool =
	case f(x) of
		false => false
		| true => forall(f)(L);

(forall(oddP)) ([1,3,5,7]);
(forall(oddP)) ([1,3,5,7,10]);


"----------------------- Question 7 -----------------------";
(*** 7 ***)
(*编写函数：*)
(*treeFilter: (‘a -> bool) -> ‘a tree -> ‘a option tree*)
(*将树中满足条件P（ ‘a -> bool ）的节点封装成option类型保留，否则替换成NONE。*)
datatype 'a tree = Empty
				   | Node of 'a tree * 'a * 'a tree;
fun treeFilter (f : 'a -> bool) (Empty : 'a tree) : 'a option tree = Empty
	| treeFilter (f : 'a -> bool) ((Node(lt, x, rt)) : 'a tree) : 'a option tree =
	case f(x) of
		false => Node(treeFilter(f)(lt), NONE, treeFilter(f)(rt))
		| true => Node(treeFilter(f)(lt), SOME(x), treeFilter(f)(rt));

val T : int tree = Node (Node (Empty, 1, Empty),3 ,Node (Empty, 5, Empty));
(treeFilter(oddP)) (T);
val T : int tree = Node (Node (Empty, 2, Empty),4 ,Node (Empty, 6, Empty));
(treeFilter(oddP)) (T);
