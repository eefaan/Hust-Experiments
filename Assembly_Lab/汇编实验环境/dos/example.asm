.386
DATA  SEGMENT  USE16
BUF    DB  50
            DB  0                  ���뻺����
            DB  50 DUP��0��
    CRLF  DB  0DH��0AH����$��
DATA  ENDS
STACK SEGMENT USE16 STACK
      DB  200 DUP(0)
STACK ENDS
CODE SEGMENT USE16
START��MOV  AX��DATA
            MOV  DS��AX
            LEA   DX��BUF
            MOV  AH��10          �����ַ���
            INT   21H
            LEA   DX��CRLF
            MOV  AH��9          ����س�����
            INT   21H
            MOV  BX��BUF+1
            MOV  BYTE  PTR  BUF+2[BX]����$��
            LEA   DX�� BUF+2
            MOV  AH��9        ����һ�����ǰ��������ַ���
            INT   21H
            MOV  AX��4C00H
            INT   21H
CODE   ENDS
END  START
