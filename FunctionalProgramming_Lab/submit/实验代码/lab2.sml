"----------------------- Question 1 -----------------------";
(*** 1 ***)
(*编写函数reverse和reverse’，要求：*)
(*函数类型均为：int list->int list，功能均为实现输出表参数的逆序输出；*)
(*函数reverse不能借助任何帮助函数；函数reverse’可以借助帮助函数，时间复杂度为O(n)。*)
fun reverse ([] : int list) : int list = []
	| reverse (x::L : int list) : int list = reverse L @ [x];

reverse [1,3,5];

fun pick_front ([] : int list, LF : int list) : int list = LF
	| pick_front (x::L : int list, LF : int list) : int list = pick_front(L, x::LF);

fun reverse' ([] : int list) : int list = []
	| reverse' (x::L : int list) : int list = pick_front(L, [x]);

reverse' [1,3,5,7];


"----------------------- Question 2 -----------------------";
(*** 2 ***)
(*编写函数 interleave: int list * int list -> int list，该函数能实现两个int list数据的合并，且两个list中的元素在结果中交替出现，直至其中一个int list数据结束，而另一个int list数据中的剩余元素则直接附加至结果数据的尾部。如：*)
(*interleave([2],[4]) = [2,4]*)
(*interleave([2,3],[4,5]) = [2,4,3,5]*)
(*interleave([2,3],[4,5,6,7,8,9]) = [2,4,3,5,6,7,8,9]*)
(*interleave([2,3],[ ]) = [2,3]*)
fun interleave ([] : int list, [] : int list) : int list = []
	| interleave ([] : int list, L : int list) : int list = L
	| interleave (L : int list, [] : int list) : int list = L
	| interleave (x::X : int list, y::Y : int list) : int list = x::y::interleave(X, Y);

interleave ([1,3,5],[2,4,6,8,10]);


"----------------------- Question 3 -----------------------";
(*** 3 ***)
(*编写函数listToTree: int list -> tree，将一个表转换成一棵平衡树。*)
(*提示：可调用split函数，split函数定义如下：
如果L非空，则存在L1, x, L2，满足：
	split L = (L1, x, L2) 	且 
	L = L1 @ x :: L2 		且 
	length(L1)和length(L2)差值小于1。*)
datatype tree = Empty
				| Node of tree * int * tree;
fun split ([] : int list) : (int list * int * int list) = ([], 0, []) 
	| split (L : int list) : (int list * int * int list) = 
		let val ll : int list = List.take (L, length L div 2)
			val mid : int = List.nth (L, length L div 2)
			val rl : int list = List.drop (L, length L div 2 + 1)
		in (ll, mid, rl)
		end;
fun listToTree ([] : int list) : tree = Empty
	| listToTree (L : int list) : tree = 
		let val(ln, mid, rn) = split(L)
		in Node(listToTree(ln), mid, listToTree(rn))
		end;

listToTree [1,3,5,7,9,10,11];


"----------------------- Question 4 -----------------------";
(*** 4 ***)
(*编写函数revT: tree -> tree，对树进行反转，使trav(revT t) = reverse(trav t)。（trav为树的中序遍历函数）。*)
(*假设输入参数为一棵平衡二叉树，验证程序的正确性，并分析该函数的执行性能（work和span）。*)
fun revT (Empty : tree) : tree = Empty
	| revT (Node(lt:tree, mid:int, rt:tree)) : tree = Node(revT rt, mid, revT lt);

val T : tree = Node (Node (Empty, 1, Empty),3 ,Node (Empty, 5, Empty));
revT T;

fun trav (Empty : tree) : int list = []
	| trav (Node(lt:tree, mid:int, rt:tree)) : int list = trav lt @ [mid] @ trav rt;
trav (revT T);
reverse (trav T);


"----------------------- Question 5 -----------------------";
(*** 5 ***)
(*编写函数binarySearch: tree * int -> bool。*)
(*当输入参数1为有序树时，如果树中包含值为参数2的节点，则返回true；否则返回false。*)
(*要求：程序中请使用函数Int.compare（系统提供），不要使用<, =, >。*)
(*datatype order = GREATER | EQUAL | LESS
case Int.compare(x1, x2) of
	GREATER => * x1 > x2 *
    | EQUAL => * x1 = x2 *
    | LESS => * x1 < x2 *)
fun binarySearch (Empty : tree, x : int) : bool = false
	| binarySearch ((Node(lt:tree, value:int, rt:tree)) : tree, x : int) = 
	case Int.compare(value, x) of
		GREATER => binarySearch(lt, x)
		| EQUAL => true
		| LESS => binarySearch(rt, x);

binarySearch (T, 3);
binarySearch (T, 2);
