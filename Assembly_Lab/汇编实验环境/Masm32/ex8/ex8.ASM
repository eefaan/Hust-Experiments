.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
_strlen  proto :DWORD
_f2to10  proto :DWORD
flash_rate proto :DWORD,:DWORD
cursor_shop2 proto

include      ex8.INC

include      C:\Masm32\INCLUDE\windows.inc
include      C:\Masm32\INCLUDE\user32.inc
include      C:\Masm32\INCLUDE\kernel32.inc
include      C:\Masm32\INCLUDE\gdi32.inc
include      C:\Masm32\INCLUDE\shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

good	    struct
	     goodname   db  10 dup(0)
	     in_price   dw  0
	     out_price  dw  0
	     in_num     dw  0
	     out_num    dw  0
	     rate       dw  0
good      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'test5.1',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'I am CSIE1601 efaan.',0
AverageMsg   db       'Caculate Done.',0
hInstance    dd       0
CommandLine  dd       0

shop1	 good  <>
	     good  <'PEN',35,56,70,25,0>
			 good  <'BOOK',12,30,25,5,0>
			 good  <'BAG',5,10,10,10,0>
			 good  <'PENCIL',5,10,10,10>
			 good  <'RULER',5,10,10,10>
	     good  3 dup(<>)
shop2	 good  <>
	     good  <'BOOK',12,28,20,15,0>
			 good  <'PEN',35,50,30,24,0>
			 good  <'BAG',5,10,10,10,0>
			 good  <'RULER',5,10,10,7>
			 good  <'PENCIL',5,10,10,10>
	     good  3 dup(<>)

msg_name     db       'NAME',0
msg_inprice  db       'IN_PRICE',0
msg_outprice db       'OUT_PRICE',0
msg_innum    db       'IN_NUM',0
msg_outnum   db       'OUT_NUM',0
msg_rate     db       'AVR(%)',0

temp_num		 dd       0
temp_1			 dd				0
temp_2			 dd				0
in_good      db				0,0,0,0,0,0,0,0,0,0,0,0
NUM 				 dd				0
N equ 5

.code
Start:
	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL

		 .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF

		 .ELSEIF uMsg == WM_COMMAND
		    .IF     wParam == IDM_FILE_EXIT
			    invoke SendMessage,hWnd,WM_CLOSE,0,0
		    .ELSEIF wParam == IDM_ACTION_AVERAGE
					invoke flash_rate,offset shop1+20,offset shop2+20
					invoke MessageBox,hWnd,addr AverageMsg,addr AppName,0
				.ELSEIF wParam == IDM_ACTION_LIST
					invoke Display,hWnd
		    .ELSEIF wParam == IDM_HELP_ABOUT
			    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
		    .ENDIF

     ; .ELSEIF uMsg == WM_PAINT
	     ; redraw window again

		 .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hWnd:DWORD
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
             LOCAL  hdc:HDC
             invoke GetDC,hWnd
             mov    hdc,eax
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_inprice,8
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_outprice,9
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_innum,6
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_outnum,7
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_rate,6
             ;;
						 mov esi,20
						 mov ebx,offset shop1
						 add esi,ebx
						 mov dx,1;counter
						 ;di-location   title    length
				lopa_in:
						 cmp byte ptr [esi],0
						 jz lopa_out
						 mov di,30
						 imul di,dx
						 push dx
						 add di,10

						 invoke _strlen,esi
             invoke TextOut,hdc,XX+0*XX_GAP,di,esi,ecx
						 add esi,10

						 mov ebx,offset temp_num
						 invoke _f2to10,esi
						 invoke _strlen,ebx
             invoke TextOut,hdc,XX+1*XX_GAP,di,ebx,ecx
						 add esi,2

						 invoke _f2to10,esi
						 invoke _strlen,ebx
             invoke TextOut,hdc,XX+2*XX_GAP,di,ebx,ecx
						 add esi,2

						 invoke _f2to10,esi
						 invoke _strlen,ebx
             invoke TextOut,hdc,XX+3*XX_GAP,di,ebx,ecx
						 add esi,2

						 invoke _f2to10,esi
						 invoke _strlen,ebx
             invoke TextOut,hdc,XX+4*XX_GAP,di,ebx,ecx
						 add esi,2

						 invoke _f2to10,esi
						 invoke _strlen,ebx
             invoke TextOut,hdc,XX+5*XX_GAP,di,ebx,ecx
						 add esi,2

						 pop dx
						 inc dx
             jmp lopa_in
				lopa_out:
						 ret
Display      endp


;函数名：STRLEN
;函数功能：计算字符串的长度
_strlen  proc  addr_strHead:DWORD
				push eax
				push ebx
				push edx
				push esi
				push edi

				mov ecx,0
				mov edx,addr_strHead

				_count_in:
				cmp byte ptr [edx],0
				jz _count_out
				inc ecx
				inc edx

				jmp _count_in
				_count_out:

				pop edi
				pop esi
				pop edx
				pop ebx
				pop eaX
				ret
_strlen  endp

_f2to10  proc  addr_numHead:DWORD
				push eax
				push ebx
				push ecx
				push edx
				push esi
				push edi

				mov ebx,offset temp_num
				mov esi,addr_numHead
				mov ax,word ptr [esi]
				or ax,ax
				JNS count_in

				mov dl,'-'
				mov byte ptr[ebx],dl
				inc ebx
				NOT ax
				INC ax

	count_in:
				MOV cx,0
				MOV di,10
	disp1:
				MOV dx,0
				DIV di
				PUSH dx
				INC cx
				OR  ax,ax
				JNE disp1

	disp2:
				pop dx
				ADD dl,30H
				mov byte ptr[ebx],dl
				inc ebx
				dec cx
				jnz disp2
				mov byte ptr[ebx],0

				pop edi
				pop esi
				pop edx
				pop ecx
				pop ebx
				pop eaX
				ret
_f2to10  endp

flash_rate proc  ga1:dword, gb1:dword
      ;刷新所有商品利润率
			MOV EAX,ga1;shop1 good1
			MOV CX,N

			LOPA_FLASH:
						LEA EDI,temp_1;+07e0h
						MOV [EDI],EAX
						LEA EDI,temp_2;+07e0h
						MOV [EDI],ECX

						MOV EDI,EAX
						MOV NUM,EDI
						;shop1
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[EDI+10];进货价
						MOV BX,DS:[EDI+14];进货量
						MUL EBX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EBX,0
						MOV AX,DS:[EDI+12];销售价
						MOV BX,DS:[EDI+16];已售量
						MUL EBX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EBX,100
						MUL EBX

						MOV EDX,0
						MOV EBX,0
						CDQ
						IDIV ECX

						; MOV DS:[DI+18],AX
						MOV EBX,EAX;shop2利润率存入ebx

            MOV ESI,gb1
            CALL cursor_shop2

						;计算shop2中利用率
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[EDI+10];进货价
						MOV DX,DS:[EDI+14];进货量
						MUL EDX
						MOV ECX,EAX;进货*进货→ecx;
						MOV EAX,0
						MOV EDX,0
						MOV AX,DS:[EDI+12];销售价
						MOV DX,DS:[EDI+16];已售量
						MUL EDX;销售*已售→eax
						SUB EAX,ECX;减法结果→eax
						MOV EDX,100
						MUL EDX

						MOV EDX,0
						CDQ
						IDIV ECX
						; MOV DS:[SI+18],AX
						;求均值
						ADD AX,BX
						CWD
						MOV CX,2
						IDIV CX
						MOV ESI,NUM
						MOV DS:[ESI+18],AX;均值存入shop1

			MOV EAX,temp_1
			ADD EAX,20
			MOV ECX,temp_2
			DEC CX
			JNZ LOPA_FLASH
      ret
flash_rate	endp

;NUM->shop1中商品地址
;esi->shop2首地址
;传出时edi->shop2中商品地址
cursor_shop2 proc
      push eax
      push ebx
      push ecx
      push edx
      push esi

      ;向in_good中复制商品名
      MOV EBX,NUM
      MOV CX,10
      LEA EDI,in_good
      MOV ESI,0
COPY:
      MOV al,[EBX][ESI]
      MOV byte PTR [EDI],al
      INC EBX
      INC EDI
      DEC CX
      JNZ COPY

      pop  ESI
      push ESI ;取店铺二商品的偏移地址赋值给S
      MOV DX , 0
      SUB ESI , 20
      ;查找第2个店铺中的商品
CHECK_GOOD:
      ADD ESI , 20 ;SI用来存储商品的第一个字符的地址
      CMP DX , N  ;比较DH与N用来判断是否查找完毕
      JZ  cursor_out
      INC DX
      MOV EDI ,ESI      ;将BX初始化为0
      MOV CX,9
      MOV EBX,0
      CHECK_GOOD_NAME:
            MOV AL , [EDI]   ;使用寄存器间接寻址赋值
            CMP BYTE PTR [in_good+EBX] , AL    ;若有字符不同，则进入CMP3比较下一商品名称
            JNZ CHECK_GOOD
            INC EDI
            INC EBX
            dec CX
            JNZ CHECK_GOOD_NAME

      MOV EDI,ESI
cursor_out:
      pop esi
      pop edx
      pop ecx
      pop ebx
      pop eax
      ret
cursor_shop2 endp


             end  Start
