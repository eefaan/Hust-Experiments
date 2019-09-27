(*3 + 4;
3 + 2.0;
it + 6;
val it = "hello";
it + "world";
it + 5;
val a = 5;
a = 6;
a + 8; 
val twice = (fn x => 2 * x);
twice a;
let x = 1 in x end;
foo;
[1, "foo"];
*)

"----------------------- Question 2 -----------------------";
(**** 2 ****)
(*函数sum用于求解整数列表中所有整数的和，函数定义如下：*)
(* sum : int list -> int 		*)
(* REQUIRES: true		*)
(* ENSURES: sum(L) evaluates to the sum of the integers in L. *)
fun sum [ ] = 0
	| sum (x :: L) = x + (sum L);

(*完成函数mult的编写，实现求解整数列表中所有整数的乘积。*)
(* mult : int list -> int 		*)
(* REQUIRES: true		*)
(* ENSURES: mult(L) evaluates to the product of the integers in L. *)
fun mult [ ] = 1		(* FILL IN *)
	| mult (x :: L) = x * (mult L);	(* FILL IN *)

sum [1,3,5];
mult [1,3,5];


"----------------------- Question 3 -----------------------";
(**** 3 ****)
(*完成如下函数Mult: int list list -> int的编写,该函数调用mult 实现int list list中所有整数乘积的求解。*)
(* mult : int list list -> int 	*)
(* REQUIRES: true		*)
(* ENSURES: mult(R) evaluates to the product of all the integers in the lists of R. *)
fun Mult [ ] = 1	(* FILL IN *)
	| Mult (r :: R) = mult r * (Mult R);	(* FILL IN *)

Mult [[1,3,5],[2]];


"----------------------- Question 4 -----------------------";
(**** 4 ****)
(*函数mult’定义如下，试补充其函数说明，指出该函数的功能。*)
(* mult’ : int list * int -> int 			*)
(* REQUIRES: true				*)
(* ENSURES: mult’(L, a) …  *FILL IN* *)
fun mult' ([ ], a) = a
	| mult' (x :: L, a) = mult' (L, x * a);
(*利用mult’定义函数Mult’ : int list list * int -> int，使对任意整数列表的列表R和整数a，该函数用于计算a与列表R中所有整数的乘积。该函数框架如下所示，试完成代码的编写。*)
fun Mult' ([ ], a) = a	(* FILL IN *)
	| Mult' (r :: R, a) = mult' (r, a) * Mult' (R, 1);	(* FILL IN *)

mult' ([1,3,5],2);
Mult' ([[1,3,5],[2]],2);


"----------------------- Question 5 -----------------------";
(**** 5 ****)
(*编写递归函数square实现整数平方的计算，即square n = n * n。要求：程序中可调用函数double，但不能使用整数乘法（*）运算。*)
(* double : int -> int *)
(* REQUIRES: n >= 0 *)
(* ENSURES: double n evaluates to 2 * n.*)
fun double (0 : int) : int = 0
	| double n = 2 + double (n - 1);
fun square (0 : int) : int = 0
	| square n = if n > 0 then square(n-1) + double(n-1) + 1 else
				 square(~n);

square 100;
square ~10;


"----------------------- Question 6 -----------------------";
(**** 6 ****)
(*定义函数divisibleByThree: int -> bool，以使当n为3的倍数时，divisibleByThree n为true，否则为false。注意：程序中不能使用取余函数’mod’。*)
(* divisibleByThree : int -> bool 	*)
(* REQUIRES: true				*)
(* ENSURES: divisibleByThree n evaluates to true if n is a multiple of 3 and to false otherwise *)
fun divisibleByThree 0 = true
	| divisibleByThree 1 = false
	| divisibleByThree 2 = false
	| divisibleByThree n = if n > 0 then divisibleByThree (n-3) else
						   divisibleByThree(~n);

divisibleByThree 3;
divisibleByThree 2;
divisibleByThree ~6;
divisibleByThree ~8;
divisibleByThree 99;


"----------------------- Question 7 -----------------------";
(**** 7 ****)
(*函数evenP为偶数判断函数，即当且仅当该数为偶数时返回true。其代码描述如下：*)
(* evenP : int -> bool 		*)
(* REQUIRES: n >= 0 		*)
(* ENSURES: evenP n evaluates to true iff n is even. *)
fun evenP (0 : int) : bool = true
	| evenP 1 = false
	| evenP n = if n > 0 then evenP (n - 2) else
				evenP(~n);
(*试编写奇数判断函数oddP: int -> bool，当且仅当该数为奇数时返回true。注意：代码不要调用函数evenP或mod。*)
fun oddP (0 : int) : bool = false
	| oddP 1 = true
	| oddP n = if n > 0 then oddP (n - 2) else
			   oddP(~n);

evenP 2;
evenP ~3;
oddP ~2;
oddP 3;
