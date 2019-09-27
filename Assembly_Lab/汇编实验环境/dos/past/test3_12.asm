EXTRN GA1:BYTE, GB1:BYTE, in_good:BYTE,print_num:NEAR
PUBLIC fun3,fun4,fun5
.386
STACK SEGMENT USE16 PARA STACK 'STACK'
			DB 200 DUP(0)
STACK ENDS

DATA 	SEGMENT USE16 PUBLIC'DATA'
temp_1 DW 0
temp_2 DW 0
FLAG   DW 0
NUM    DW 0
NUM1   DW 0
N		   EQU	30
in_good_s DB	10
					DB	0
					DB 	10 DUP(0)

function1 DB  'this will be f1!',0DH,0AH,'$'
function2 DB  'this will be f2!',0DH,0AH,'$'
function3 DB  'this will be f3!',0DH,0AH,'$'
function3_1 DB 'The commodity rate of profits is completed!',0DH,0AH,'$'
function4 DB  'this will be f4!',0DH,0AH,'$'
function4_1 DB 'Rank Goods with Profit margins is completed!',0DH,0AH,'$'
function5 DB  'this will be f5!',0DH,0AH,'$'
function5_1 DB  'Press any key to continue!',0DH,0AH,'$'

SHOP1_s 				DB  'SHOP1:$';
SHOP2_s					DB  'SHOP2:$'
GOOD_NAME_s 		DB	'  GOOD NAME:       $'
OUT_PRICE_s			DB	'  SELLING PRICE:   $'
IN_NUM_s				DB	'  REPLENISH NUM:   $'
OUT_NUM_s				DB  '  SELLING NUM:     $'
IN_PRICE_s			DB  '  REPLENISH PRICE: $'
PROFIT_s				DB  '  PROFIT(%):       $'
CRLF_s		DB 	0DH,0AH,'$'

DATA	ENDS

PRINT MACRO A
      push dx
			LEA DX,A;+07e0h
			MOV AH,9
			INT 21H
			pop dx
			ENDM

CODE 	SEGMENT USE16 PARA PUBLIC 'CODE'
			ASSUME DS:DATA,CS:CODE,SS:STACK

; Author:
; partner:
; function: 首先计算SHOP1中第一个商品的利润率PR1，
;						然后在SHOP2网店中寻找到该商品，也计算其利润率PR2。
;						最后求出该商品的平均利润率APR=(PR1+PR2)/2，
;						并保存到SHOP1的利润率字段中。
;						重复上述步骤，依次将每个商品的平均利润率计算出来。回到功能三（1）。
fun3 proc
			push ax
			push si
			push di

			; MOV AX,DATA1
			; MOV ES,AX

			CALL flash_rate
			LEA DX,function3_1;+07e0h
			MOV AH,9
			INT 21H

			pop di
			pop si
			pop ax
			ret
fun3 endp

; Author:
; partner:
; function: 对SHOP2中的每个商品按照平均利润率的大小排名，
;						排名信息存放到SHOP2中商品的利润率字段中。回到功能三（1）
fun4 proc
			push ax
			push si
			push di
			push dx
			push bx
			push cx

			; MOV AX,DATA1
			; MOV ES,AX

			MOV DX,N
			MOV SI,OFFSET GA1
		  MOV NUM1,0
      SUB NUM1,20
f4_LOOP4:	MOV CX,N
          ADD NUM1,20
			    MOV BX,0
			    SUB BX,20
			    MOV NUM,0
f4_LOOP1: ADD BX,20
          CMP BX,NUM1
					JZ f4_LOOP1
          MOV AX,18[BX][SI]
					MOV BP,NUM1
          CMP DS:18[BP][SI],AX
					JNZ f4_LOOP2
					JMP f4_LOOP3
f4_LOOP2:	MOV AX,18[BX][SI]
          MOV BP,NUM1
          CMP DS:18[BP][SI],AX
					JNS f4_LOOP3
					INC NUM
					JMP f4_LOOP3
f4_LOOP3:
          DEC CX
			    JNZ f4_LOOP1
		  MOV AX,NUM
			CALL change_in_good
			CALL find_name
			MOV DS:18[DI],AX
			DEC DX
			JNZ f4_LOOP4
			LEA DX,function4_1;+07e0h
			MOV AH,9
			INT 21H

      pop cx
			pop bx
			pop dx
			pop di
			pop si
			pop ax
			ret
fun4 endp

; Author:
; partner:
; function: 将SHOP1和SHOP2中的所有商品信息显示到屏幕上，包括平均利润率和排名
;						（替代了商品原有的利润率字段）。
;						具体的显示格式自行定义
;						（可以分网店显示，也可以按照商品排名显示，等等，
;						显示方式可以作为子程序的入口参数）。回到功能三（1）。
fun5 proc
			push ax
			push si
			push di
			push ax
			push bx
			push cx
			push dx

			; MOV AX,DATA1
			; MOV ES,AX

			MOV DI,0
f5_LOOP1:
      MOV FLAG,0
      MOV CX,N
      INC DI
			CMP DI,3
			JZ f5_EXIT
			MOV BX,0
			SUB BX,20
			CMP DI,1
			JNZ f5_LOOP2
			MOV SI,OFFSET GA1
			PRINT SHOP1_s
			PRINT CRLF_s
			JMP f5_LOOP3
f5_LOOP2:
      MOV SI,OFFSET GB1
			PRINT SHOP2_s
			PRINT CRLF_s
f5_LOOP3:
      ADD BX,20
      PRINT GOOD_NAME_s
			MOV NUM1,0
			MOV NUM,BX
f5_LOOP6:
      MOV DL,BYTE PTR [BX][SI]
			MOV AH,2
			INT 21H
			INC BX
      INC NUM1
			CMP NUM1,10
			JNZ f5_LOOP6
      PRINT CRLF_s
			MOV BX,NUM

      PRINT OUT_PRICE_s
      MOV AX,12[BX][SI]
      CALL print_num
      PRINT CRLF_s

      PRINT IN_NUM_s
      MOV AX,14[BX][SI]
      CALL print_num
      PRINT CRLF_s

      PRINT OUT_NUM_s
      MOV AX,16[BX][SI]
      CALL print_num
      PRINT CRLF_s

			PRINT IN_PRICE_s
			MOV AX,10[BX][SI]
			CALL print_num
			PRINT CRLF_s

			PRINT PROFIT_s
			MOV AX,18[BX][SI]
			CALL print_num
			PRINT CRLF_s
			PRINT CRLF_s

      INC FLAG
			CMP FLAG,2
			JZ f5_LOOP5
f5_LOOP4:
			DEC CX
			JNZ f5_LOOP3
			JMP f5_LOOP1
f5_LOOP5:
      MOV FLAG,0
      PRINT function5_1
			MOV AH,1
			INT 21H
			JMP f5_LOOP4
f5_EXIT:
      pop dx
			pop cx
			pop bx
			pop ax
			pop di
			pop si
			pop ax
			ret
fun5 endp

; Author: liu yifan
; partner: shi ruize
; function: 两店铺商品同顺序情况下，刷新所有商品利润率。
flash_rate proc        ;刷新所有商品利润率
      push eax
			push ebx
     	push ecx
      push edx
			push si
			push di
			; 现场保护

			LEA AX, [GA1];shop1 good1
			MOV CX,N

			LOPA_FLASH:
						LEA DI,temp_1;+07e0h
						MOV [DI],AX
						LEA DI,temp_2;+07e0h
						MOV [DI],CX

						MOV DI,AX
						MOV NUM1,DI
						;shop1
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[DI+10];进货价
						MOV BX,DS:[DI+14];进货量
						MUL EBX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[DI+12];销售价
						MOV BX,DS:[DI+16];已售量
						MUL EBX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EBX,100
						MUL EBX

						MOV EDX,0
						MOV EBX,0
						CDQ
						IDIV ECX;;;;;;;;;;;;;;;;;;;;;;;

						; MOV DS:[DI+18],AX
						MOV EBX,EAX;shop2利润率存入ebx

						MOV SI,0
						CALL change_in_good
						CALL find_name

						;计算shop2中利用率
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[DI+10];进货价
						MOV DX,DS:[DI+14];进货量
						MUL EDX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[DI+12];销售价
						MOV DX,DS:[DI+16];已售量
						MUL EDX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EDX,100
						MUL EDX

						MOV EDX,0
						CDQ
						IDIV ECX;;;;;;;;;;;;;;;;;;;;;;;;
						; MOV DS:[SI+18],AX
						;求均值
						ADD AX,BX
						CWD
						MOV CX,2
						IDIV CX;;;;;;;;;;;;;;;;;;;;;;;;;
						MOV SI,NUM1
						MOV DS:[SI+18],AX;均值存入shop1


			MOV AX,temp_1
			ADD AX,20
			MOV CX,temp_2
			DEC CX
			JNZ LOPA_FLASH

      pop  di
			pop	 si
			pop	 edx
			pop  ecx
			pop  ebx
			pop  eax
      ret
flash_rate	endp


change_in_good proc
			push ax
			push bx
			push cx
			push dx
			push si
			push di


			MOV BX,NUM1
			MOV CX,10
			LEA DI,in_good_s+2
			change_LOOP:
			MOV DL,[BX][SI]
			MOV [DI],DL
			INC BX
			INC DI
			DEC CX
			JNZ change_LOOP

			pop di
			pop si
			pop dx
			pop cx
			pop bx
			pop ax
			ret
change_in_good endp

find_name proc
			push ax
			push bx
			push cx
			push dx
			push si

			MOV SI , OFFSET GB1  ;取店铺二商品的偏移地址赋值给S
			MOV DH , 0
			SUB SI , 20

			;CMP3、CMP4形成二重循环，用于查找两个店铺中的商品
CMP3:
			ADD SI , 20 ;SI用来存储商品的第一个字符的地址
			CMP DH , N  ;比较DH与N用来判断是否查找完毕
			JZ  fn_EXIT
			INC DH
			MOV DI , SI      ;将BX初始化为0
			MOV CX,9
			MOV BX,0
CMP4:
			MOV DL , [DI]   ;使用寄存器间接寻址赋值
			CMP BYTE PTR [in_good_s+2+BX] , DL    ;若有字符不同，则进入CMP3比较下一商品名称
			JNZ CMP3
			INC DI
			INC BX
			dec CX
			JNZ CMP4
			MOV DI,SI

fn_EXIT:
		 	pop si
		  pop dx
		  pop cx
		  pop bx
		  pop ax
		  ret
find_name endp

CODE	 	ENDS
			END
