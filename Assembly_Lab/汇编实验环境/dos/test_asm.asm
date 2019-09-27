.386
.model small,c
public cal_rank,flash_rate
ASSUME DS:_DATA
.DATA
N       EQU 2
NUM1    DW  0
NUM1    DW  0
temp_1  DW  0
temp_2  DW  0
in_good DW  0
.code

flash_rate proc  ga1:word, gb1:word
     ;刷新所有商品利润率
      ; push eax
			; push ebx
     	; push ecx
      ; push edx
			; push si
			; push di
			; 现场保护
      MOV N,2
			MOV AX,ga1;shop1 good1
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            push ax
            push bx
            push cx
            push di
            MOV BX,NUM1
      			MOV CX,10
      			LEA DI,in_good+2
      change_LOOP1:
      			MOV ax,[BX][SI]
      			MOV [DI],ax
      			INC BX
      			INC DI
      			DEC CX
      			JNZ change_LOOP1
            pop di
            pop cx
            pop bx
            pop ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            push ax
            push bx
            push cx
            push dx
            push si

            MOV SI , gb1  ;取店铺二商品的偏移地址赋值给S
            MOV dx , 0
            SUB SI , 20

            ;CMP3、CMP4形成二重循环，用于查找两个店铺中的商品
      CMP31:
            ADD SI , 20 ;SI用来存储商品的第一个字符的地址
            CMP dx , N  ;比较DH与N用来判断是否查找完毕
            JZ  fn_EXIT1
            INC DH
            MOV DI , SI      ;将BX初始化为0
            MOV CX,9
            MOV EBX,0
      CMP41:
            MOV DL , [DI]   ;使用寄存器间接寻址赋值
            CMP BYTE PTR [in_good+2+EBX] , DL    ;若有字符不同，则进入CMP3比较下一商品名称
            JNZ CMP31
            INC DI
            INC EBX
            dec CX
            JNZ CMP41
            MOV DI,SI

      fn_EXIT1:
            pop si
            pop dx
            pop cx
            pop bx
            pop ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

      ; pop  di
			; pop	 si
			; pop	 edx
			; pop  ecx
			; pop  ebx
			; pop  eax
      ret
flash_rate	endp


cal_rank proc ga1:word, gb1:word
			push ax
			push si
			push di
			push dx
			push bx
			push cx

      MOV N,2
			MOV DX,N
			MOV SI,ga1
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
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            push ax
            push bx
            push ax
            push bx
            push cx
            push di
            MOV BX,NUM1
      			MOV CX,10
      			LEA DI,in_good+2
      change_LOOP1:
      			MOV ax,[BX][SI]
      			MOV [DI],ax
      			INC BX
      			INC DI
      			DEC CX
      			JNZ change_LOOP1
            pop di
            pop cx
            pop bx
            pop ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            push ax
            push bx
            push cx
            push dx
            push si

            MOV SI , gb1  ;取店铺二商品的偏移地址赋值给S
            MOV dx , 0
            SUB SI , 20

            ;CMP3、CMP4形成二重循环，用于查找两个店铺中的商品
      CMP31:
            ADD SI , 20 ;SI用来存储商品的第一个字符的地址
            CMP dx , N  ;比较DH与N用来判断是否查找完毕
            JZ  fn_EXIT1
            INC DH
            MOV DI , SI      ;将BX初始化为0
            MOV CX,9
            MOV EBX,0
      CMP41:
            MOV DL , [DI]   ;使用寄存器间接寻址赋值
            CMP BYTE PTR [in_good+2+EBX] , DL    ;若有字符不同，则进入CMP3比较下一商品名称
            JNZ CMP31
            INC DI
            INC EBX
            dec CX
            JNZ CMP41
            MOV DI,SI

      fn_EXIT1:
            pop si
            pop dx
            pop cx
            pop bx
            pop ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			MOV DS:18[DI],AX
			DEC DX
			JNZ f4_LOOP4
			; LEA DX,function4_1;+07e0h
			; MOV AH,9
			; INT 21H

      pop cx
			pop bx
			pop dx
			pop di
			pop si
			pop ax
			ret
cal_rank endp

;
; change_in_good proc
; 			push ax
; 			push bx
; 			push cx
; 			push dx
; 			push si
; 			push di
;
;
; 			MOV BX,NUM1
; 			MOV CX,10
; 			LEA DI,in_good+2
; 			change_LOOP:
; 			MOV DL,[BX][SI]
; 			MOV [DI],DL
; 			INC BX
; 			INC DI
; 			DEC CX
; 			JNZ change_LOOP
;
; 			pop di
; 			pop si
; 			pop dx
; 			pop cx
; 			pop bx
; 			pop ax
; 			ret
; change_in_good endp
;
; find_name proc
; 			push ax
; 			push bx
; 			push cx
; 			push dx
; 			push si
;
; 			MOV SI , OFFSET GB1  ;取店铺二商品的偏移地址赋值给S
; 			MOV DH , 0
; 			SUB SI , 20
;
; 			;CMP3、CMP4形成二重循环，用于查找两个店铺中的商品
; CMP3:
; 			ADD SI , 20 ;SI用来存储商品的第一个字符的地址
; 			CMP DH , N  ;比较DH与N用来判断是否查找完毕
; 			JZ  fn_EXIT
; 			INC DH
; 			MOV DI , SI      ;将BX初始化为0
; 			MOV CX,9
; 			MOV BX,0
; CMP4:
; 			MOV DL , [DI]   ;使用寄存器间接寻址赋值
; 			CMP BYTE PTR [in_good+2+BX] , DL    ;若有字符不同，则进入CMP3比较下一商品名称
; 			JNZ CMP3
; 			INC DI
; 			INC BX
; 			dec CX
; 			JNZ CMP4
; 			MOV DI,SI
;
; fn_EXIT:
; 		 	pop si
; 		  pop dx
; 		  pop cx
; 		  pop bx
; 		  pop ax
; 		  ret
; find_name endp

			END
