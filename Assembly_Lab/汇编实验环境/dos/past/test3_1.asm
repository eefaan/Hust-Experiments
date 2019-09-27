EXTRN fun3:NEAR,fun4:NEAR,fun5:NEAR
PUBLIC GA1, GB1, in_good,print_num
.386
STACK SEGMENT USE16 PARA STACK 'STACK'
			DB 200 DUP(0)
STACK ENDS
DATA 	SEGMENT USE16 PUBLIC 'DATA'

; temp DW 0,0,0
temp_good 	DW 0
count DW 0

BNAME	DB	'liu yifan',0,0 			 ;老板姓名（必须是自己名字的拼音）
BPASS	DB  'test',0,0,0    			 ;密码
N		 	EQU	30
;商品名称（10个字节，名称不足部分补0），进货价(字类型)，销售价（字类型），
;进货总数（字类型），已售数量（字类型），
;利润率（%）【=（销售价*已售数量-进货价*进货总数）*100/（进货价*进货总数），字类型】
S1  	DB 	'SHOP1',0            ;网店名称，用0结束
			GA1   DB  'PEN',7 DUP(0)  		 ;商品名称
     				DW  35,56,70,25,0	  		 ;利润率还未计算
			GA2   DB  'BOOK',6 DUP(0) 		 ;商品名称
     				DW  12,30,25,5,0	 			 ;利润率还未计算
			GAN   DB  N-2 DUP( 'Temp-Value',15,0,20,0,30,0,2,0,0,0)
			;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
S2 		DB  'SHOP2',0            ;网店名称，用0结束
			GB1   DB  'BOOK',6 DUP(0)			 ;商品名称
     				DW  12,28,20,15,0 	 	 	 ;利润率还未计算
			GB2   DB  'PEN',7 DUP(0)  		 ;商品名称
     				DW  35,50,30,24,0 			 ;利润率还未计算
			GBN   DB  N-2 DUP( 'Temp-Value',15,0,20,0,30,0,2,0,0,0)

ASHOP					DB  'Input SHOP Please:$'
ANAME 				DB	'Input NAME Please:$'
APASS					DB  'Input PASSWORDS Please:$'
AGOOD					DB  'Input GOODSNAME Please:$'
LOGIN_FAIL 		DB  'LOGIN FAIL! Try It Again.',0DH,0AH,'$'
LOGIN_SUCCESS DB  'LOGIN SUCCESS!',0DH,0AH,'$'
FIND_FAIL 		DB  'FIND FAIL! Try It Again.',0DH,0AH,'$'
FIND_SUCCESS 	DB  'FIND SUCCESS! Details:',0DH,0AH,'$'
FIND_CHANGE 	DB  'FIND SUCCESS! Make Your Changes:',0DH,0AH,'$'
FLASH_SUCCESS DB  'FLASH SUCCESS!',0DH,0AH,'$'
CHANGE_SUCCESS DB 'CHANGE SUCCESS!',0DH,0AH,'$'
FIND_SHOP_FAIL DB 'WRONG SHOP NAME! Try It Again.',0DH,0AH,'$'
MENU_ROOT		  DB  'FUNCTION MENU:',0DH,0AH,
							  	'  1=Find Goods Info',0DH,0AH,
							  	'  2=Modify Goods Info',0DH,0AH,
								  '  3=Calculate Goods Profit margins',0DH,0AH,
  								'  4=Rank Goods with Profit margins',0DH,0AH,
								  '  5=List Goods',0DH,0AH,
								  '  6=Exit',0DH,0AH,
								  'Choose the function:','$'
MENU_USER		  DB  'FUNCTION MENU:',0DH,0AH,
								  '  1=Find Goods Info',0DH,0AH,
								  '  6=Exit',0DH,0AH,
								  'Choose the function:','$'
WRONG_INPUT 	DB  'WRONG INPUT! Try It Again.',0DH,0AH,'$'

SHOP1 				DB  'SHOP1:$';
SHOP2					DB  'SHOP2:$'
GOOD_NAME 		DB	'  GOOD NAME:       $'
OUT_PRICE			DB	'  SELLING PRICE:   $'
IN_NUM				DB	'  REPLENISH NUM:   $'
OUT_NUM				DB  '  SELLING NUM:     $'
IN_PRICE			DB  '  REPLENISH PRICE: $'
PROFIT				DB  '  PROFIT(%):       $'
RANK					DB	'  RANK:            $'

CURSOR	DB	'>>>$'
AUTH		DB  1
CRLF		DB 	0DH,0AH,'$'

in_choosenum 	DB  2
							DB  3 DUP(0)

in_name DB	11
				DB	0
				DB 	11 DUP(0)
in_pwd	DB	7
				DB	0
				DB 	7  DUP(0)
in_good DB	10
				DB	0
				DB 	10 DUP(0)
in_shop DB  6
				DB  7 DUP(0)
in_num2 DB  5
				DB  6 DUP(0)
dec_num DB  20 DUP(0)

DATA	ENDS

SCANF MACRO A
			LEA DX,A
			MOV AH,10
			INT 21H
			ENDM
PRINT MACRO A
			LEA DX,A
			MOV AH,9
			INT 21H
			ENDM

CODE 	SEGMENT USE16 PUBLIC 'CODE'
			ASSUME CS:CODE,DS:DATA,SS:STACK
START:MOV AX,DATA						;DS:数据段
			MOV DS,AX

BEGIN:
			CALL login	;调用子程序login提示用户输入用户密码 并对输入进行相应处理
									;执行完毕时AUTH=0 则为游客
									;执行完毕时AUTH=1 则为管理员
									;其他情况下 子程序不会执行结束

			CALL menu		;调用子程序menu依据使用者登陆情况 输出操作菜单
									;若为游客（AUTH=0） 仅提供功能1、6
									;若为管理员（AUTH=1） 提供功能1-6

			JMP BEGIN		;执行对应功能后回到登陆界面

_OUT:
			MOV AH,4CH
			INT 21H



; Author: liu yifan
; partner: shi ruize
; function: 提示用户输入用户密码 并对输入进行相应处理
;						执行完毕时AUTH=0 则为游客
;						执行完毕时AUTH=1 则为管理员
;						其他情况下 不会结束
login proc
			LOGIN_IN:;提示输入用户名
						LEA DX,ANAME
						MOV AH,9
						INT 21H
						;输入用户名
						LEA DX,in_name
						MOV AH,10
						INT 21H
						LEA DX,CRLF
						MOV AH,9
						INT 21H
						MOV BL,in_name+1
						MOV BH,0												;取输入的实际字符个数到BX
						MOV BYTE PTR in_name+2[BX],'$'	;输入串尾补'$'

						;判断输入用户名正常/为回车/为q
						CMP in_name+1,1;长度是否为1
						JZ Is1;是是则跳转到Not1
						;否则继续执行判断
						CMP in_name+1,0;是否直接回车
						JNZ Not_Q;不是则跳转到NotQ
						;否则输入了回车 执行
						MOV AUTH,0
						ret	;跳过输入密码 进入展示模块
						;否则不是 执行以下部分
			Is1:	CMP in_name+2,'q'
						JNZ Not_Q;不退出则提示输入密码
						;否则执行退出
						JMP _OUT	;退出程序

			Not_Q:;提示输入密码
						LEA DX,APASS
						MOV AH,9
						INT 21H
						;输入密码
						LEA DX,in_pwd
						MOV AH,10
						INT 21H
						LEA DX,CRLF
						MOV AH,9
						INT 21H
						MOV BL,in_pwd+1
						MOV BH,0												;取输入的实际字符个数到BX
						MOV BYTE PTR in_pwd+2[BX],'$'	;输入串尾补'$'

			CHECK:;循环校对用户名与密码
						;校对用户名
						MOV CL,in_name+1			;以字符串长度为循环次数
						MOV CH,0
						MOV SI,OFFSET BNAME;变址
						MOV DI,OFFSET in_name
						ADD DI,2;
						INT 21H								;exit
			LOPA_NAME:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ LOGIN_ERROR
						INC SI								;自增变址
						INC DI
						DEC CX								;循环end
						JNZ LOPA_NAME
						;若比较完输入串重的所有字符
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,'$'							;判断inname是否\0结尾
						JNZ LOGIN_ERROR				;若不是 重新输入
						CMP AL,0							;是否同到结尾
						JNZ LOGIN_ERROR				;若不是 重新输入

						;校对密码
						MOV CL,in_pwd+1			;以字符串长度为循环次数
						MOV CH,0
						MOV SI,OFFSET BPASS;变址
						MOV DI,OFFSET in_pwd+2
						INT 21H								;exit
			LOPA_PWD:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ LOGIN_ERROR
						INC SI								;自增变址
						INC DI
						DEC CX								;循环end
						JNZ LOPA_PWD
						;若比较完输入串重的所有字符
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,'$'							;判断inpwd是否\0结尾
						JNZ LOGIN_ERROR				;若不是 重新输入
						CMP AL,0						;是否同到结尾
						JNZ LOGIN_ERROR				;若不是 重新输入
						;校对成功
						LEA DX,LOGIN_SUCCESS
						MOV AH,9
						INT 21H
						LEA DX,CRLF
						MOV AH,9
						INT 21H
						MOV AUTH,1
						ret

			LOGIN_ERROR:
						;提示输入用户名
						LEA DX,LOGIN_FAIL
						MOV AH,9
						INT 21H
						LEA DX,CRLF
						MOV AH,9
						INT 21H
						JMP LOGIN_IN
login endp

; Author: liu yifan
; partner: shi ruize
; function: 调用子程序menu依据使用者登陆情况 输出操作菜单
;						若为游客（AUTH=0） 仅提供功能1、6
;						若为管理员（AUTH=1） 提供功能1-6
menu proc
			MENU_IN:
						CMP AUTH,0
						JZ USER_IN	;为0 为游客提供功能1、6
												;否则 为管理员提供功能1-6
			ROOT_IN:
						PRINT MENU_ROOT

						MOV AH,1
						INT 21H

						CMP AL,31H
						JNZ ROOT_NOT1
						PRINT CRLF
						CALL fun1
						JMP MENU_OUT
			ROOT_NOT1:
						CMP AL,32H
						JNZ ROOT_NOT2
						PRINT CRLF
						CALL fun2
						JMP MENU_OUT
			ROOT_NOT2:
						CMP AL,33H
						JNZ ROOT_NOT3
						PRINT CRLF
						CALL fun3
						JMP MENU_OUT
			ROOT_NOT3:
						CMP AL,34H
						JNZ ROOT_NOT4
						PRINT CRLF
						CALL fun4
						JMP MENU_OUT
			ROOT_NOT4:
						CMP AL,35H
						JNZ ROOT_NOT5
						PRINT CRLF
						CALL fun5
						JMP MENU_OUT
			ROOT_NOT5:
						CMP AL,36H
						JNZ ROOT_NOT6
						JMP _OUT
			ROOT_NOT6:
						CMP AL,0DH
						JNZ ROOT_NOTBACK
						PRINT CRLF
						ret
			ROOT_NOTBACK:
						PRINT CRLF
						PRINT WRONG_INPUT
						PRINT CRLF
						JMP MENU_IN

			USER_IN:
						PRINT MENU_USER

						MOV AH,1
						INT 21H

						CMP AL,31H
						JNZ USER_NOT1
						PRINT CRLF
						CALL fun1
						JMP MENU_OUT
			USER_NOT1:
						CMP AL,36H
						JNZ USER_NOT6
						JMP _OUT
			USER_NOT6:
						CMP AL,0DH
						JNZ USER_NOTBACK
						PRINT CRLF
						ret
			USER_NOTBACK:
						PRINT CRLF
						PRINT WRONG_INPUT
						PRINT CRLF
						JMP MENU_IN

			MENU_OUT:
						PRINT CRLF
						JMP MENU_IN
menu endp

; Author: liu yifan
; partner: shi ruize
; function: 提示用户输入要查询的商品名称。
;						若未能在第一个网店中找到该商品，重新提示输入商品名称。
;						若只输入回车，则回到功能三（1）。
;						找到该商品之后，按照：
;							“SHOP1，商品名称，销售价，进货总数，已售数量”顺序显示该商品的信息，
;						同时还要将“SHOP2”中该商品的信息也显示出来。显示之后回到功能三（1）。
fun1 proc
			push ax
			push si
			push di
			fun1_IN:;直接跳入AUTH=0 用户密码校对成功AUTH=1
						;提示输入货物
						PRINT AGOOD
						;输入货物
						LEA DX,in_good
						MOV AH,10
						INT 21H
						PRINT CRLF
						MOV BL,in_good+1
						MOV BH,0												;取输入的实际字符个数到BX
						MOV BYTE PTR in_good+2[BX],'$'	;输入串尾补'$'

						;否则继续执行判断
						CMP in_good+1,0;是否直接回车
						JZ fun1_OUT;是则ret后回到菜单
						;否则在shop1中查找good

						;校对商品名
						MOV CX,N			;以总商品数为循环次数
						LEA AX, GA1;shop1 good1
						LEA BX, in_good+2;in_good name
						LOPA_SHOP1:
									LEA DI,temp_good
									MOV DS:[DI],AX
									MOV SI,AX
									MOV DI,BX

									MOV BH,0
									MOV BL,in_good+1			;以输入商品名称长度为循环次数
									LOPA_GOOD1:
												MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
												MOV AH,DS:[DI]
												CMP AH,AL
												JNZ OUT_LOPA_GOOD1
												INC SI								;自增变址
												INC DI
												DEC BX								;循环end
												JNZ LOPA_GOOD1

									;若比较完输入串中的所有字符
									MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
									MOV AH,DS:[DI]
									CMP AH,'$'							;判断inname是否\0结尾
									JNZ OUT_LOPA_GOOD1				;若不是 重新输入
									CMP AL,0							;是否同到结尾
									JNZ OUT_LOPA_GOOD1				;若不是 重新输入
									;出循环则已查找到商品
									PRINT CRLF
									PRINT FIND_SUCCESS

									MOV DI,temp_good
									PRINT SHOP1
									PRINT CRLF

									PRINT GOOD_NAME
									PRINT in_good+2
									PRINT CRLF

									PRINT OUT_PRICE
									MOV AX,DS:[DI+12]
									CALL print_num
									PRINT CRLF

									PRINT IN_NUM
									MOV AX,DS:[DI+14]
									CALL print_num
									PRINT CRLF

									PRINT OUT_NUM
									MOV AX,DS:[DI+16]
									CALL print_num
									PRINT CRLF

									;若是游客 结束输出
									CMP AUTH,0
									JZ SHOP2_IN

									;否则继续输出
									PRINT IN_PRICE
									MOV AX,DS:[DI+10]
									CALL print_num
									PRINT CRLF

						; MOV AX,DS:[DI+18]
						; .IF AX==0
						; 			JMP SHOP2_IN
						; .ELSE
									PRINT PROFIT
									MOV AX,DS:[DI+18]
									CALL print_num
									PRINT CRLF
						; .ENDIF

									SHOP2_IN:
									;初始化shop2中的计算
									MOV CL,N			;以总商品数为循环次数
									MOV CH,0
									LEA AX, GB1;shop2 good1
									LEA BX, in_good+2;in_good name
									JMP LOPA_SHOP2
						OUT_LOPA_GOOD1:
						MOV AX,temp_good
						ADD AX,20
						LEA BX,in_good+2;in_good name
						DEC CX
						JNZ LOPA_SHOP1
						;出循环则未查找到商品
						PRINT CRLF
						PRINT FIND_FAIL
						PRINT CRLF
						JMP fun1_IN


						LOPA_SHOP2:;shop2中查找商品
									MOV DL,in_good+1			;以输入商品名称长度为循环次数
									MOV DH,0
									LEA DI,temp_good
									MOV DS:[DI],AX
									MOV SI,AX
									MOV DI,BX
									LOPA_GOOD2:
												MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
												MOV AH,DS:[DI]
												CMP AH,AL
												JNZ OUT_LOPA_GOOD2
												INC SI								;自增变址
												INC DI
												DEC DX								;循环end
												JNZ LOPA_GOOD2
									;若比较完输入串重的所有字符
									MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
									MOV AH,DS:[DI]
									CMP AH,'$'							;判断inname是否\0结尾
									JNZ OUT_LOPA_GOOD2				;若不是 重新输入
									CMP AL,0							;是否同到结尾
									JNZ OUT_LOPA_GOOD2				;若不是 重新输入

									;出循环则查找到商品，输出商品信息
									MOV DI,temp_good
									PRINT SHOP2
									PRINT CRLF

									PRINT GOOD_NAME
									PRINT in_good+2
									PRINT CRLF

									PRINT OUT_PRICE
									MOV AX,DS:[DI+12]
									CALL print_num
									PRINT CRLF

									PRINT IN_NUM
									MOV AX,DS:[DI+14]
									CALL print_num
									PRINT CRLF

									PRINT OUT_NUM
									MOV AX,DS:[DI+16]
									CALL print_num
									PRINT CRLF

									;若是游客 结束输出
									CMP AUTH,0
									JZ fun1_OUT

									;否则继续输出
									PRINT IN_PRICE
									MOV  AX,DS:[DI+10]
									CALL print_num
									PRINT CRLF

									PRINT RANK
									MOV AX,DS:[DI+18]
									CALL print_num
									PRINT CRLF
									JMP fun1_OUT

						OUT_LOPA_GOOD2:
						MOV AX,temp_good
						ADD AX,20
						DEC CX
						JNZ LOPA_SHOP2
fun1_OUT:
			pop di
			pop si
			pop ax
			ret
fun1 endp

; Author:
; partner:
; function: 提示用户输入要修改信息的商品名称（先指定网店名称）。
;						若未能在指定网店中找到该商品，重新提示输入网店名称和商品名称。
;						若只输入回车，则回到功能三（1）。
;						找到该商品之后，按照：进货价，销售价，进货总数的次序，
;						逐一先显示原来的数值，然后输入新的数值
;						（若输入有错，则重新对该项信息进行显示与修改。
;						若直接回车，则不修改该项信息）。
;						当对三项信息都处理完毕后，回到功能三（1）
fun2 proc
			push ax
			push si
			push di

fun2_IN:
			;提示输入商店名
			PRINT ASHOP
			;输入密码
			LEA DX,in_shop
			MOV AH,10
			INT 21H
			PRINT CRLF
			MOV BL,in_shop+1
			MOV BH,0												;取输入的实际字符个数到BX
			MOV BYTE PTR in_shop+2[BX],'$'	;输入串尾补'$'

			;否则继续执行判断
			CMP in_shop+1,0;是否直接回车
			JZ fun2_OUT;是则ret后回到菜单
			;否则比对是否为shop1

			;校对商店名
			LEA SI, S1;shop1
			LEA DI, in_shop+2;in_shop name

			MOV CH,0
			MOV CL,in_shop+1			;以输入商品名称长度为循环次数
			LOPA_SHOP1_NAME:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ OUT_LOPA_SHOP1_NAME
						INC SI								;自增变址
						INC DI
						DEC CX								;循环end
						JNZ LOPA_SHOP1_NAME
			;若比较完输入串中的所有字符
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,'$'							;判断inname是否\0结尾
			JNZ OUT_LOPA_SHOP1_NAME				;若不是 判断2
			CMP AL,0							;是否同到结尾
			JNZ OUT_LOPA_SHOP1_NAME				;若不是 判断2
			;出循环则已确认是店铺1

			;提示输入货物
			PRINT AGOOD
			;输入货物
			LEA DX,in_good
			MOV AH,10
			INT 21H
			PRINT CRLF
			MOV BL,in_good+1
			MOV BH,0												;取输入的实际字符个数到BX
			MOV BYTE PTR in_good+2[BX],'$'	;输入串尾补'$'
			CMP in_good+1,0;是否直接回车
			JZ fun2_OUT;是则ret后回到菜单
			;否则在shop1中查找good
			;校对商品名
			MOV CX,N			;以总商品数为循环次数
			LEA AX, GA1;shop1 good1
			LEA BX, in_good+2;in_good name
			JMP LOPA_SHOP


OUT_LOPA_SHOP1_NAME:
			;校对商店名
			LEA SI, S2;shop1
			LEA DI, in_shop+2;in_shop name

			MOV CH,0
			MOV CL,in_shop+1			;以输入商品名称长度为循环次数
			LOPA_SHOP2_NAME:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ OUT_LOPA_SHOP2_NAME
						INC SI								;自增变址
						INC DI
						DEC CX								;循环end
						JNZ LOPA_SHOP2_NAME
			;若比较完输入串中的所有字符
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,'$'							;判断inname是否\0结尾
			JNZ OUT_LOPA_SHOP2_NAME				;若不是 重新输入
			CMP AL,0							;是否同到结尾
			JNZ OUT_LOPA_SHOP2_NAME				;若不是 重新输入
			;出循环则已确认是店铺二

			;提示输入货物
			PRINT AGOOD
			;输入货物
			LEA DX,in_good
			MOV AH,10
			INT 21H
			PRINT CRLF
			MOV BL,in_good+1
			MOV BH,0												;取输入的实际字符个数到BX
			MOV BYTE PTR in_good+2[BX],'$'	;输入串尾补'$'
			CMP in_good+1,0;是否直接回车
			JZ fun2_OUT;是则ret后回到菜单
			;否则在shop1中查找good
			;校对商品名
			MOV CX,N			;以总商品数为循环次数
			LEA AX, GB1;shop1 good1
			LEA BX, in_good+2;in_good name

LOPA_SHOP:
			LEA DI,temp_good
			MOV DS:[DI],AX
			MOV SI,AX
			MOV DI,BX
			MOV BH,0
			MOV BL,in_good+1			;以输入商品名称长度为循环次数
			LOPA_GOOD:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ OUT_LOPA_GOOD
						INC SI								;自增变址
						INC DI
						DEC BX								;循环end
						JNZ LOPA_GOOD
						;若比较完输入串中的所有字符
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,'$'							;判断inname是否\0结尾
						JNZ OUT_LOPA_GOOD				;若不是 重新输入
						CMP AL,0							;是否同到结尾
						JNZ OUT_LOPA_GOOD				;若不是 重新输入
						;出循环则已查找到商品
						PRINT CRLF
						PRINT FIND_CHANGE
						MOV DI,temp_good

			BACK_1:
						PRINT IN_PRICE
						MOV  AX,DS:[DI+10]
						CALL print_num
						PRINT CURSOR
						CALL f10to2
						PRINT CRLF
						CMP  CH,2;error
						JZ 	 BACK_1
						CMP  CH,0;JMP
						JZ	 BACK_2
						MOV  DS:[DI+10],BX

			BACK_2:
						PRINT OUT_PRICE
						MOV  AX,DS:[DI+12]
						CALL print_num
						PRINT CURSOR
						CALL f10to2
						PRINT CRLF
						CMP  CH,2;error
						JZ 	 BACK_2
						CMP  CH,0;JMP
						JZ	 BACK_3
						MOV  DS:[DI+12],BX

			BACK_3:
						PRINT IN_NUM
						MOV  AX,DS:[DI+14]
						CALL print_num
						PRINT CURSOR
						CALL f10to2
						PRINT CRLF
						CMP  CH,2;error
						JZ 	 BACK_3
						CMP  CH,0;JMP
						JZ   DONE
						MOV  DS:[DI+14],BX

			DONE:
						PRINT CHANGE_SUCCESS
						JMP fun2_OUT

			OUT_LOPA_GOOD:
			MOV AX,temp_good
			ADD AX,20
			LEA BX,in_good+2;in_good name
			DEC CX
			JNZ LOPA_SHOP
			;出循环则未查找到商品
			PRINT CRLF
			PRINT FIND_FAIL
			PRINT CRLF
			JMP fun2_IN

fun2_OUT:
			pop di
			pop si
			pop ax
			ret

OUT_LOPA_SHOP2_NAME:
			PRINT CRLF
			PRINT FIND_SHOP_FAIL
			PRINT CRLF
			JMP fun2_IN

fun2 endp


; Author: liu yifan
; partner: shi ruize
; function: 将AX中的值以十进制形式输出。
print_num proc       ;输出内存中数字
			push ax
			push bx
			push cx
			push dx
			push si
			push di
			OR AX,AX
			JNS count_in
			NOT AX
			INC AX
			push AX
			MOV DL,2DH
			MOV AH,2
			INT 21H
			pop AX
count_in:
			MOV CX,0
     	MOV BX,10
disp1:
			MOV DX,0
      DIV BX
      PUSH DX
      INC CX
    	OR  AX,AX
     	JNE disp1
disp2:
      MOV AH,2
     	POP DX
     	ADD DL,30H
      INT 21H
      LOOP disp2
			pop DI
			pop SI
			pop dx
			pop cx
			pop bx
			pop AX
			ret
print_num endp

; Author: liu yifan
; partner: shi ruize
; function: 从用户输入中读取四位数字存入in_num
;						若输入回车ch=0
;						若输入1～9之外的字符ch=2
;						若输入正确ch=1
f10to2 proc
			push di
			push si

			LEA DX,in_num2
			MOV AH,10
			INT 21H

			CMP in_num2+1,0
			JZ exit_0

			mov  bx,0
			lea  di,in_num2+2
			mov  al,in_num2+1
judge:
			mov  dx,0
			mov  dl,ds:[di]
      sub  dl,30h
      jl   exit_error   ;输入出错
      cmp  dl,9d
      jg   exit_error   ;输入出错
      inc  di

			imul bx,10
			add  bx,dx

			dec  al
			jnz  judge
endl:
      mov  ch,1
      jmp  out_decin
exit_0:
			mov  ch,0
			jmp  out_decin
exit_error:
			mov  ch,2
			jmp  out_decin
out_decin:
			pop si
			pop di
			ret
f10to2 endp

CODE 	ENDS
			END START
