.386
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

DlgProc PROTO :DWORD,:DWORD,:DWORD,:DWORD

.data
DlgName db "MyDialog",0
AppName db "Our Second Dialog Box",0
TestString db "Wow! I'm in an edit box now",0

.data?
hInstance HINSTANCE ?
CommandLine LPSTR ?
buffer db 512 dup(?)

.const
IDC_EDIT        equ 3000
IDC_BUTTON      equ 3001
IDC_EXIT        equ 3002
IDM_GETTEXT     equ 32000
IDM_CLEAR       equ 32001
IDM_EXIT        equ 32002


.code
start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	invoke DialogBoxParam, hInstance, ADDR DlgName,NULL,addr DlgProc,NULL
	invoke ExitProcess,eax

DlgProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	.IF uMsg==WM_INITDIALOG
		invoke GetDlgItem, hWnd,IDC_EDIT
		invoke SetFocus,eax
	.ELSEIF uMsg==WM_CLOSE
		invoke SendMessage,hWnd,WM_COMMAND,IDM_EXIT,0
	.ELSEIF uMsg==WM_COMMAND
		mov eax,wParam
		.IF lParam==0
			.IF ax==IDM_GETTEXT
				invoke GetDlgItemText,hWnd,IDC_EDIT,ADDR buffer,512
				invoke MessageBox,NULL,ADDR buffer,ADDR AppName,MB_OK
			.ELSEIF ax==IDM_CLEAR
				invoke SetDlgItemText,hWnd,IDC_EDIT,NULL
			.ELSEIF ax==IDM_EXIT
				invoke EndDialog, hWnd,NULL
			.ENDIF
		.ELSE
			mov edx,wParam
			shr edx,16
			.if dx==BN_CLICKED
				.IF ax==IDC_BUTTON
					invoke SetDlgItemText,hWnd,IDC_EDIT,ADDR TestString
                        .ELSEIF ax==IDC_EXIT
					invoke SendMessage,hWnd,WM_COMMAND,IDM_EXIT,0
				.ENDIF
			.ENDIF
		.ENDIF
	.ELSE
		mov eax,FALSE
		ret
	.ENDIF
	mov eax,TRUE
	ret
DlgProc endp
end start

