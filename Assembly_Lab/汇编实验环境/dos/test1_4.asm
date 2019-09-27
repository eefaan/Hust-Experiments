.386
STACK   SEGMENT  USE16 STACK
        DB  200 DUP(0)
STACK   ENDS

DATA    SEGMENT USE16
XUEHAO  DB 8 DUP(0)
NUM     DB '0504'
DATA    ENDS

CODE    SEGMENT USE16
ASSUME 	CS: CODE, DS: DATA, SS: STACK

START:  MOV AX,DATA
        MOV DS,AX

        MOV SI, OFFSET XUEHAO
        MOV BX, OFFSET NUM

        MOV AH,[BX]                ;寄存器间接寻址
        MOV [SI],AH

        MOV AH,[BX+1]			         ;变址寻址
        MOV [SI+1],AH

        MOV SI,2			   	         ;基址加变址
				MOV AH,[BX][SI]
				MOV XUEHAO+2,AH

        MOV BYTE PTR DS:[3H],34H   ;直接寻址

        INT 21
CODE    ENDS
        END START
