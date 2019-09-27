; #########################################################################

      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive

; #########################################################################

      include dbmacros.asm

      include \masm32\include\windows.inc
      include \masm32\include\user32.inc
      include \masm32\include\kernel32.inc
      include \masm32\include\comctl32.inc

      includelib \masm32\lib\user32.lib
      includelib \masm32\lib\kernel32.lib
      includelib \masm32\lib\comctl32.lib      

; #########################################################################

      ;=============
      ; Local macros
      ;=============

      szText MACRO Name, Text:VARARG
        LOCAL lbl
          jmp lbl
            Name db Text,0
          lbl:
        ENDM

      m2m MACRO M1, M2
        push M2
        pop  M1
      ENDM

      return MACRO arg
        mov eax, arg
        ret
      ENDM

        ;=================
        ; Local prototypes
        ;=================
        WinMain PROTO :DWORD,:DWORD,:DWORD,:DWORD
        WndProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
        TopXY PROTO   :DWORD,:DWORD
        PushButton PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

    .data
        szDisplayName db "Demo of DBSHOW.DLL",0
        CommandLine   dd 0
        hWnd          dd 0
        hInstance     dd 0
        hStatus       dd 0

    .code

start:
        invoke GetModuleHandle, NULL
        mov hInstance, eax

        invoke GetCommandLine
        mov CommandLine, eax

        invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
        invoke ExitProcess,eax

; #########################################################################

WinMain proc hInst     :DWORD,
             hPrevInst :DWORD,
             CmdLine   :DWORD,
             CmdShow   :DWORD

        ;====================
        ; Put LOCALs on stack
        ;====================

        LOCAL wc   :WNDCLASSEX
        LOCAL msg  :MSG

        LOCAL Wwd  :DWORD
        LOCAL Wht  :DWORD
        LOCAL Wtx  :DWORD
        LOCAL Wty  :DWORD

        invoke InitCommonControls

        ;==================================================
        ; Fill WNDCLASSEX structure with required variables
        ;==================================================

        mov wc.cbSize,         sizeof WNDCLASSEX
        mov wc.style,          CS_HREDRAW or CS_VREDRAW \
                               or CS_BYTEALIGNWINDOW
        mov wc.lpfnWndProc,    offset WndProc
        mov wc.cbClsExtra,     NULL
        mov wc.cbWndExtra,     NULL
        m2m wc.hInstance,      hInst   ;<< NOTE: macro not mnemonic
        mov wc.hbrBackground,  COLOR_BTNFACE+1
        mov wc.lpszMenuName,   NULL
        mov wc.lpszClassName,  offset szClassName
          invoke LoadIcon,hInst,500    ; icon ID
        mov wc.hIcon,          eax
          invoke LoadCursor,NULL,IDC_ARROW
        mov wc.hCursor,        eax
        mov wc.hIconSm,        0

        invoke RegisterClassEx, ADDR wc

        ;================================
        ; Centre window at following size
        ;================================

        mov Wwd, 500
        mov Wht, 350

        invoke GetSystemMetrics,SM_CXSCREEN
        invoke TopXY,Wwd,eax
        mov Wtx, eax

        invoke GetSystemMetrics,SM_CYSCREEN
        invoke TopXY,Wht,eax
        mov Wty, eax

        szText szClassName,"Template_Class"

        invoke CreateWindowEx,WS_EX_LEFT,
                              ADDR szClassName,
                              ADDR szDisplayName,
                              WS_OVERLAPPEDWINDOW,
                              Wtx,Wty,Wwd,Wht,
                              NULL,NULL,
                              hInst,NULL
        mov   hWnd,eax

        invoke LoadMenu,hInst,600  ; menu ID
        invoke SetMenu,hWnd,eax

        invoke ShowWindow,hWnd,SW_SHOWNORMAL
        invoke UpdateWindow,hWnd

      ;===================================
      ; Loop until PostQuitMessage is sent
      ;===================================

    StartLoop:
      invoke GetMessage,ADDR msg,NULL,0,0
      cmp eax, 0
      je ExitLoop
      invoke TranslateMessage, ADDR msg
      invoke DispatchMessage,  ADDR msg
      jmp StartLoop
    ExitLoop:

      return msg.wParam

WinMain endp

; #########################################################################

WndProc proc hWin   :DWORD,
             uMsg   :DWORD,
             wParam :DWORD,
             lParam :DWORD

    LOCAL Rct :RECT
    LOCAL caW :DWORD
    LOCAL caH :DWORD


    .if uMsg == WM_COMMAND
    ;======== Process buttons ========

        .if wParam == 500
            invoke GetTickCount
            ShowReturn hWin, eax       ; show return value in 3 formats

        .elseif wParam == 501
            invoke GetTickCount
            UseTitleBar hWin,eax,2     ; show return value on Title Bar

        .elseif wParam == 502
            invoke GetTickCount
            UseStatusBar hStatus,eax,3 ; show return value on Status Bar

        .elseif wParam == 503
            ShowRegisters hWin,2       ; display registers

        .elseif wParam == 504

            ;---------------------
             ClockitStart              ; start clocking
            ;---------------------
            mov eax, 0
            stt:
              inc eax
              cmp eax, 10000000
              jne stt
            ;---------------------
             ClockitStop hWin,1        ; show milliseconds duration
            ;---------------------

    ;======== menu commands ========

        .elseif wParam == 1000
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL
        .elseif wParam == 1900
            szText TheMsg,"Assembler, pure and simple"
            invoke MessageBox,hWin,ADDR TheMsg,ADDR szDisplayName,MB_OK
        .endif

    ;====== end menu commands ======

    .elseif uMsg == WM_CREATE

        szText bText1,"Show Return Value"
        invoke PushButton,ADDR bText1,hWin,20,20,150,25,500

        szText bText2,"Use Title Bar"
        invoke PushButton,ADDR bText2,hWin,20,50,150,25,501

        szText bText3,"Use Status Bar"
        invoke PushButton,ADDR bText3,hWin,20,80,150,25,502

        szText bText4,"Show Registers"
        invoke PushButton,ADDR bText4,hWin,20,110,150,25,503

        szText bText5,"Clock It"
        invoke PushButton,ADDR bText5,hWin,20,140,150,25,504

        ;----------------------
        ; Create the status bar
        ;----------------------

        invoke CreateStatusWindow,WS_CHILD or WS_VISIBLE or \
                                   SBS_SIZEGRIP,0, hWin, 200
        mov hStatus, eax

    .elseif uMsg == WM_SIZE

        invoke GetWindowRect,hStatus,ADDR Rct
        mov eax, Rct.bottom
        sub eax, Rct.top
        sub lParam[2], eax

        invoke MoveWindow,hStatus,0,lParam[0],lParam[2],lParam[0],TRUE

    ;.elseif uMsg == WM_CLOSE
        ;szText TheText,"Please Confirm Exit"
        ;invoke MessageBox,hWin,ADDR TheText,ADDR szDisplayName,MB_YESNO
          ;.if eax == IDNO
          ;  return 0
          ;.endif

    .elseif uMsg == WM_DESTROY
        invoke PostQuitMessage,NULL
        return 0 
    .endif

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; ########################################################################

TopXY proc wDim:DWORD, sDim:DWORD

    shr sDim, 1      ; divide screen dimension by 2
    shr wDim, 1      ; divide window dimension by 2
    mov eax, wDim    ; copy window dimension into eax
    sub sDim, eax    ; sub half win dimension from half screen dimension

    return sDim

TopXY endp

; ########################################################################

PushButton proc lpText:DWORD,hParent:DWORD,
                a:DWORD,b:DWORD,wd:DWORD,ht:DWORD,ID:DWORD

    szText btnClass,"BUTTON"

    invoke CreateWindowEx,0,
            ADDR btnClass,lpText,
            WS_CHILD or WS_VISIBLE,
            a,b,wd,ht,hParent,ID,
            hInstance,NULL

    ret

PushButton endp

; ########################################################################

end start
