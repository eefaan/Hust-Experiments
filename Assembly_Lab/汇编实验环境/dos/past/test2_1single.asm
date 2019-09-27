.386
STACK SEGMENT USE16 STACK
			DB 200 DUP(0)
STACK ENDS
DATA 	SEGMENT USE16

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
			GA3   DB  'BAG',7 DUP(0) 		 ;商品名称
     				DW  12,30,2500,5,0	 			 ;利润率还未计算
			GAN   DB  N-3 DUP( 'Temp-Value',15,0,20,0,30,0,2,0,0,0)
			;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
S2 		DB  'SHOP2',0            ;网店名称，用0结束
			GB1   DB  'BOOK',6 DUP(0)			 ;商品名称
     				DW  12,28,20,15,0 	 	 	 ;利润率还未计算
			GB2   DB  'PEN',7 DUP(0)  		 ;商品名称
     				DW  35,50,30,24,0 			 ;利润率还未计算
			GB3   DB  'BAG',7 DUP(0) 		 ;商品名称
     				DW  12,30,25,5,0	 			 ;利润率还未计算
			GBN   DB  N-3 DUP( 'Temp-Value',15,0,20,0,30,0,2,0,0,0)

ANAME DB	'Input NAME Please:$'
APASS	DB  'Input PASSWORDS Please:$'
AGOOD	DB  'Input GOODSNAME Please:$'
LOGIN_FAIL DB  'LOGIN FAIL! Try It Again.',0DH,0AH,'$'
LOGIN_SUCCESS DB 'LOGIN SUCCESS!',0DH,0AH,'$'
FIND_FAIL DB  'FIND FAIL! Try It Again.',0DH,0AH,'$'
FIND_SUCCESS DB  'FIND SUCCESS!',0DH,0AH,'$'
GOODRANK DB 'RANK:$'

AUTH		DB  1
CRLF		DB 	0DH,0AH,'$'

in_name DB	11
				DB	0
				DB 	11 DUP(0)
in_pwd	DB	7
				DB	0
				DB 	7  DUP(0)
in_good DB	10
				DB	0
				DB 	10 DUP(0)

DATA	ENDS

CODE 	SEGMENT USE16
			ASSUME CS:CODE,DS:DATA;SS:STACK
START:MOV AX,DATA						;DS:数据段
			MOV DS,AX

LOGIN:;提示输入用户名
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
			JMP DISPLAY		;跳过输入密码 进入展示模块
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
LOPA_NAME:
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,AL
			JNZ ERRORSTART
			INC SI								;自增变址
			INC DI
			DEC CX								;循环end
			JNZ LOPA_NAME
			;若比较完输入串重的所有字符
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,'$'							;判断inname是否\0结尾
			JNZ ERRORSTART				;若不是 重新输入
			CMP AL,0							;是否同到结尾
			JNZ ERRORSTART				;若不是 重新输入

			;校对密码
			MOV CL,in_pwd+1			;以字符串长度为循环次数
			MOV CH,0
			MOV SI,OFFSET BPASS;变址
			MOV DI,OFFSET in_pwd+2
LOPA_PWD:
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,AL
			JNZ ERRORSTART
			INC SI								;自增变址
			INC DI
			DEC CX								;循环end
			JNZ LOPA_PWD
			;若比较完输入串重的所有字符
			MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
			MOV AH,DS:[DI]
			CMP AH,'$'							;判断inpwd是否\0结尾
			JNZ ERRORSTART				;若不是 重新输入
			CMP AL,0						;是否同到结尾
			JNZ ERRORSTART				;若不是 重新输入
			;校对成功
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,LOGIN_SUCCESS
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			MOV AUTH,1
			JMP DISPLAY

ERRORSTART:
			;提示输入用户名
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,LOGIN_FAIL
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START

DISPLAY:;直接跳入AUTH=0 用户密码校对成功AUTH=1
			;提示输入货物
			LEA DX,AGOOD
			MOV AH,9
			INT 21H
			;输入货物
			LEA DX,in_good
			MOV AH,10
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			MOV BL,in_good+1
			MOV BH,0												;取输入的实际字符个数到BX
			MOV BYTE PTR in_good+2[BX],'$'	;输入串尾补'$'

			;否则继续执行判断
			CMP in_good+1,0;是否直接回车
			JZ LOGIN;是则跳转到功能一login重新输入
			;否则在shop1中查找good
			CALL disptime

CALCULATE:
			;校对商品名
			MOV CL,N			;以总商品数为循环次数
			MOV CH,0
			LEA SP, [GA1];shop1 good1
			LEA BP, [in_good+2];in_good name

LOPA_SHOP1:
						MOV BL,in_good+1			;以输入商品名称长度为循环次数
						MOV BH,0
						MOV SI,SP
						MOV DI,BP
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
						;若是游客
						CMP AUTH,0
						JZ USER_OUT
						;否则计算shop1中利用率

			;此行之前为实验一任务五功能三相关代码
						MOV SI,SP
						MOV AX,DS:[SI+14];进货量
						MOV BX,DS:[SI+16];已售量
						CMP AX,BX
						JZ OUT_CALCULATE;售完则跳出循环回到功能一
						INC BX									;否则已售量自增
						MOV DS:[SI+16],BX
			;此行之后为实验一任务五功能三相关代码

						MOV SI,SP
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[SI+10];进货价
						MOV BX,DS:[SI+14];进货量
						MUL EBX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[SI+12];销售价
						MOV BX,DS:[SI+16];已售量
						MUL EBX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EBX,100
						MUL EBX

						MOV EDX,0
						MOV EBX,0
						CDQ
						IDIV ECX;;;;;;;;;;;;;;;;;;;;;;;

						MOV DS:[SI+18],AX
						MOV EBX,EAX;shop1利润率存入ebx

						;初始化shop2中的计算
						MOV CL,N			;以总商品数为循环次数
						MOV CH,0
						LEA SP, [GB1];shop2 good1
						LEA BP, [in_good+2];in_good name
						;在shop2中继续查询
						JMP LOPA_SHOP2
			OUT_LOPA_GOOD1:
			ADD SP,20
			LEA BP, [in_good+2];in_good name
			DEC CX
			JNZ LOPA_SHOP1
			;出循环则未查找到商品
			LEA DX,FIND_FAIL
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP DISPLAY

LOPA_SHOP2:;shop2中查找商品
						MOV DL,in_good+1			;以输入商品名称长度为循环次数
						MOV DH,0
						MOV SI,SP
						MOV DI,BP
			LOPA_GOOD2:
						MOV AL,DS:[SI]			;DS:[SI]的值传递给AL
						MOV AH,DS:[DI]
						CMP AH,AL
						JNZ OUT_LOPA_GOOD2
						INC SI								;自增变址
						INC DI
						DEC DX								;循环end
						JNZ LOPA_GOOD2
						;若比较完输入串中的所有字符
						MOV AL,DS:[SI]			;DS:[SI]的值传递给BUF2
						MOV AH,DS:[DI]
						CMP AH,'$'							;判断inname是否\0结尾
						JNZ OUT_LOPA_GOOD2				;若不是 重新输入
						CMP AL,0							;是否同到结尾
						JNZ OUT_LOPA_GOOD2				;若不是 重新输入

						;计算shop2中利用率
						MOV SI,SP
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[SI+10];进货价
						MOV DX,DS:[SI+14];进货量
						MUL EDX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[SI+12];销售价
						MOV DX,DS:[SI+16];已售量
						MUL EDX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EDX,100
						MUL EDX

						MOV EDX,0
						CDQ
						IDIV ECX;;;;;;;;;;;;;;;;;;;;;;;;
						MOV DS:[SI+18],AX
						;求均值
						ADD AX,BX
						CWD
						MOV CX,2
						IDIV CX;;;;;;;;;;;;;;;;;;;;;;;;;
						JMP CALCULATE
						; JMP ROOT_OUT
			OUT_LOPA_GOOD2:
			ADD SP,20
			LEA BP, [in_good+2];in_good name
			DEC CX
			JNZ LOPA_SHOP2

OUT_CALCULATE:
			CALL disptime
			JMP LOGIN

USER_OUT:;游客输出
			; MOV SI,SP
			; LEA DX,[SI]
			LEA DX,in_good+2
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START

ROOT_OUT:;店主输出
			;AX中为比值

			CMP AX,90
			JGE _OUTA
			CMP AX,50
			JGE _OUTB
			CMP AX,20
			JGE _OUTC
			CMP AX,0
			JGE _OUTD
			JMP _OUTF

_OUTA:
			MOV DL,41H
			MOV AH,2
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START
_OUTB:
			MOV DL,42H
			MOV AH,2
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START
_OUTC:
			MOV DL,43H
			MOV AH,2
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START
_OUTD:
			MOV DL,44H
			MOV AH,2
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START
_OUTF:
			MOV DL,46H
			MOV AH,2
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			LEA DX,CRLF
			MOV AH,9
			INT 21H
			JMP START

_OUT:
			MOV AH,4CH
			INT 21H

disptime proc        ;显示秒和百分秒，精度为55ms。（未保护ax寄存器）
    local timestr[8]:byte     ;0,0,'"',0,0,0dh,0ah,'$'

         push cx
         push dx
         push ds
         push ss
         pop  ds
         mov  ah,2ch
         int  21h
         xor  ax,ax
         mov  al,dh
         mov  cl,10
         div  cl
         add  ax,3030h
         mov  word ptr timestr,ax
         mov  timestr+2,'"'
         xor  ax,ax
         mov  al,dl
         div  cl
         add  ax,3030h
         mov  word ptr timestr+3,ax
         mov  word ptr timestr+5,0a0dh
         mov  timestr+7,'$'
         lea  dx,timestr
         mov  ah,9
         int  21h
         pop  ds
         pop  dx
         pop  cx
         ret
disptime	endp

CODE 	ENDS
			END START
