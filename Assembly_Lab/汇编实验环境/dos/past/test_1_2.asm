.386
STACK SEGMENT USE16 STACK
			DB 200 DUP(0)
STACK ENDS
DATA 	SEGMENT USE16
BUF1 	DB 0,1,2,3,4,5,6,7,8,9
BUF2 	DB 10 DUP(0)
BUF3 	DB 10 DUP(0)
BUF4 	DB 10 DUP(0)
hello	DB 'Press any key to begin! $'
DATA	ENDS
CODE 	SEGMENT USE16
			ASSUME CS:CODE,DS:DATA;SS:STACK
START:MOV AX,DATA						;为AX赋DATA的地址值
			MOV DS,AX							;
			MOV SI,OFFSET BUF1		;
			MOV DI,OFFSET BUF2		;
			MOV BX,OFFSET BUF3		;
			MOV BP,OFFSET BUF4		;
			MOV CX,10							;
			LEA DX,hello					;display
			MOV ah,9
						int 21h
			MOV AH,4CH   					;exit
			MOV AH,1							;scan
			INT 21H								;exit
LOPA:	MOV AL,[SI]						;DS:[SI]的值传递给BUF2
			MOV [DI],AL
			INC AL								;DS:[SI]的值自增后传递给BUF3
			MOV [BX],AL
			ADD AL,3							;DS:[SI]的值+3后传递给BUF4
			MOV DS:[BP],AL
			INC SI								;自增指针
			INC DI
			INC BP
			INC BX
			DEC CX								;循环end
			JNZ LOPA
			MOV AH,4CH
			INT 21H
CODE 	ENDS
			END START
