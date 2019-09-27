; #########################################################################

      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive

; #########################################################################

      include \masm32\include\windows.inc

      include \masm32\include\user32.inc
      include \masm32\include\kernel32.inc
      include \masm32\include\gdi32.inc
      include \masm32\include\shell32.inc

      includelib \masm32\lib\user32.lib
      includelib \masm32\lib\kernel32.lib
      includelib \masm32\lib\gdi32.lib
      includelib \masm32\lib\shell32.lib

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
        TopXY   PROTO :DWORD,:DWORD
        ListBox PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
        ListProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
        PushButton PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
        Frame3D PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
        Paint_Proc PROTO :DWORD,:DWORD


    .data
        szDisplayName db "Run EXE File",0
        CommandLine   dd 0
        hWnd          dd 0
        hInstance     dd 0
        hList         dd 0
        lpfnListProc  dd 0
        hIcon         dd 0

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
        LOCAL PathName[128]:BYTE

        ;==================================================
        ; Fill WNDCLASSEX structure with required variables
        ;==================================================

        invoke LoadIcon,hInst,500    ; icon ID
        mov hIcon, eax

        mov wc.cbSize,         sizeof WNDCLASSEX
        mov wc.style,          CS_HREDRAW or CS_VREDRAW \
                               or CS_BYTEALIGNWINDOW
        mov wc.lpfnWndProc,    offset WndProc
        mov wc.cbClsExtra,     NULL
        mov wc.cbWndExtra,     NULL
        m2m wc.hInstance,      hInst
        mov wc.hbrBackground,  COLOR_BTNFACE+1
        mov wc.lpszMenuName,   NULL
        mov wc.lpszClassName,  offset szClassName
        m2m wc.hIcon,          hIcon
          invoke LoadCursor,NULL,IDC_ARROW
        mov wc.hCursor,        eax
        mov wc.hIconSm,        0

        invoke RegisterClassEx, ADDR wc

        ;================================
        ; Centre window at following size
        ;================================

        mov Wwd, 430
        mov Wht, 277

        invoke GetSystemMetrics,SM_CXSCREEN
        invoke TopXY,Wwd,eax
        mov Wtx, eax

        invoke GetSystemMetrics,SM_CYSCREEN
        invoke TopXY,Wht,eax
        mov Wty, eax

        invoke GetCurrentDirectory,128,ADDR PathName

        szText szClassName,"Run_File_Class"

        invoke CreateWindowEx,WS_EX_OVERLAPPEDWINDOW,
                              ADDR szClassName,
                              ADDR PathName,
                              WS_OVERLAPPED or WS_SYSMENU,
                              Wtx,Wty,Wwd,Wht,
                              NULL,NULL,
                              hInst,NULL
        mov   hWnd,eax

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

    LOCAL hDC            :DWORD
    LOCAL Ps             :PAINTSTRUCT
    LOCAL PathBuffer[128]:BYTE

    .if uMsg == WM_COMMAND
    ;======== menu commands ========
        .if wParam == 503
            invoke SendMessage,hWin,WM_SYSCOMMAND,SC_CLOSE,NULL
            
        .elseif wParam == 500
            szText BackOneDir,".."
            invoke SetCurrentDirectory,ADDR BackOneDir
            invoke GetCurrentDirectory,128,ADDR PathBuffer
            invoke SendMessage,hWin,WM_SETTEXT,0,ADDR PathBuffer
          ResetJmp:  
            invoke SendMessage,hList,LB_RESETCONTENT,0,0
            szText patternf,"*.*"
            invoke SendMessage,hList,LB_DIR,
                   DDL_DIRECTORY or DDL_DRIVES,ADDR patternf

        .elseif wParam == 501
            szText GotoRoot,"\"
            invoke SetCurrentDirectory,ADDR GotoRoot
            invoke GetCurrentDirectory,128,ADDR PathBuffer
            invoke SendMessage,hWin,WM_SETTEXT,0,ADDR PathBuffer
            jmp ResetJmp

        .elseif wParam == 502
            szText AboutMsg,"Minifile Version 1.0 Copyright © 1999",13,10,\
            "Steve Hutchesson < hutch@pbq.com.au >"

            szText AboutTitle,"Assembler Minifile"
            invoke ShellAbout,hWin,ADDR AboutTitle,ADDR AboutMsg,hIcon

        .endif
    ;====== end menu commands ======

    .elseif uMsg == WM_CREATE
        invoke ListBox,5,38,411,208,hWin,600
        mov hList, eax

        invoke SetWindowLong,hList,GWL_WNDPROC,ListProc
        mov lpfnListProc, eax

        szText pattern,"*.*"
        invoke SendMessage,hList,LB_DIR,
               DDL_DIRECTORY or DDL_DRIVES,ADDR pattern

        szText Back1Dir,".."
        invoke PushButton,ADDR Back1Dir,hWin,11,11,25,21,500

        szText RootDir,"\"
        invoke PushButton,ADDR RootDir,hWin,40,11,25,21,501

        szText About,"About"
        invoke PushButton,ADDR About,hWin,340,11,70,21,502

        szText Quit,"Exit"
        invoke PushButton,ADDR Quit,hWin,266,11,70,21,503






    .elseif uMsg == WM_PAINT
        invoke BeginPaint,hWin,ADDR Ps
          mov hDC, eax
          invoke Paint_Proc,hWin,hDC
        invoke EndPaint,hWin,ADDR Ps
        return 0

    .elseif uMsg == WM_CLOSE

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

Frame3D proc hDC:DWORD,btn_hi:DWORD,btn_lo:DWORD,
             tx:DWORD, ty:DWORD, lx:DWORD, ly:DWORD,bdrWid:DWORD

    LOCAL hPen     :DWORD
    LOCAL hPen2    :DWORD
    LOCAL hpenOld  :DWORD

    invoke CreatePen,0,1,btn_hi
    mov hPen, eax
  
    invoke SelectObject,hDC,hPen
    mov hpenOld, eax

    ; ------------------------------------
    ; Save copy of parameters for 2nd loop
    ; ------------------------------------
    push tx
    push ty
    push lx
    push ly
    push bdrWid

    ; ------------

       lpOne:

        invoke MoveToEx,hDC,tx,ty,NULL
        invoke LineTo,hDC,lx,ty

        invoke MoveToEx,hDC,tx,ty,NULL
        invoke LineTo,hDC,tx,ly

        dec tx
        dec ty
        inc lx
        inc ly

        dec bdrWid
        cmp bdrWid, 0
        je lp1Out
        jmp lpOne
      lp1Out:

    ; ------------
    invoke CreatePen,0,1,btn_lo
    mov hPen2, eax
    invoke SelectObject,hDC,hPen2
    mov hPen, eax
    invoke DeleteObject,hPen
    ; ------------

    pop bdrWid
    pop ly
    pop lx
    pop ty
    pop tx

       lpTwo:

        invoke MoveToEx,hDC,tx,ly,NULL
        invoke LineTo,hDC,lx,ly

        invoke MoveToEx,hDC,lx,ty,NULL
        inc ly        
        invoke LineTo,hDC,lx,ly
        dec ly

        dec tx
        dec ty
        inc lx
        inc ly

        dec bdrWid
        cmp bdrWid, 0
        je lp2Out
        jmp lpTwo
      lp2Out:

    ; ------------
    invoke SelectObject,hDC,hpenOld
    invoke DeleteObject,hPen2

    ret

Frame3D endp

; #########################################################################

Paint_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL btn_hi   :DWORD
    LOCAL btn_lo   :DWORD
    LOCAL Rct      :RECT

    invoke GetSysColor,COLOR_BTNHIGHLIGHT
    mov btn_hi, eax

    invoke GetSysColor,COLOR_BTNSHADOW
    mov btn_lo, eax

    ; -----------------------------------------------------------------
    ; The following 2 calls draw the border around the left two buttons
    ; -----------------------------------------------------------------
    invoke Frame3D,hDC,btn_lo,btn_hi,8,8,67,34,1
    invoke Frame3D,hDC,btn_hi,btn_lo,6,6,69,36,1

    ; ------------------------------------------------------
    ; The following 2 calls draw the right window frame area
    ; ------------------------------------------------------
    invoke Frame3D,hDC,btn_lo,btn_hi,263,8,412,34,1
    invoke Frame3D,hDC,btn_hi,btn_lo,72,6,414,36,1

    ; ----------------------------------------------------------
    ; The following code draws the border around the client area
    ; ----------------------------------------------------------
    invoke GetClientRect,hWin,ADDR Rct

    add Rct.left,   1
    add Rct.top,    1
    sub Rct.right,  1
    sub Rct.bottom, 1

    invoke Frame3D,hDC,btn_hi,btn_lo,
                   Rct.left,Rct.top,
                   Rct.right,Rct.bottom,1

    add Rct.left,   2
    add Rct.top,    2
    sub Rct.right,  2
    sub Rct.bottom, 2

    invoke Frame3D,hDC,btn_lo,btn_hi,
                   Rct.left,
                   Rct.top,Rct.right,Rct.bottom,1

    return 0

Paint_Proc endp

; ########################################################################


ListBox proc a:DWORD,b:DWORD,wd:DWORD,ht:DWORD,hParent:DWORD,ID:DWORD

    szText lstBox,"LISTBOX"

    invoke CreateWindowEx,WS_EX_CLIENTEDGE,ADDR lstBox,0,
              WS_HSCROLL or WS_VISIBLE or \
              WS_BORDER or WS_CHILD or \
              LBS_HASSTRINGS or LBS_NOINTEGRALHEIGHT or \
              LBS_SORT or LBS_MULTICOLUMN,
              a,b,wd,ht,hParent,ID,hInstance,NULL

    ret

ListBox endp

; #########################################################################

ListProc proc hCtl   :DWORD,
              uMsg   :DWORD,
              wParam :DWORD,
              lParam :DWORD

    LOCAL Sel            :DWORD
    LOCAL fln            :DWORD
    LOCAL PathBuffer[128]:BYTE
    LOCAL FileBuffer [16]:BYTE
    LOCAL DirBuffer  [16]:BYTE
    LOCAL DrvBuffer   [4]:BYTE

    push esi
    push edi

    szText BkSl,"\"

    .if uMsg == WM_CHAR
      .if wParam == 13
        call ProcessFile
      .endif

    .elseif uMsg == WM_LBUTTONDBLCLK
      call ProcessFile

    .endif

    invoke CallWindowProc,lpfnListProc,hCtl,uMsg,wParam,lParam
    
    pop edi
    pop esi

    ret

    ; -----------------------------------------------------------
    ; Local Subroutines
    ; -----------------------------------------------------------

    ProcessFile:

        invoke SendMessage,hCtl,LB_GETCURSEL,0,0
        mov Sel, eax
        invoke SendMessage,hCtl,LB_GETTEXT,Sel,ADDR FileBuffer

    .if FileBuffer[0] == "["
    
        .if FileBuffer[1] == "-"  ; Change drive

            mov al, FileBuffer[2]   ; the drive letter
            lea edi, DrvBuffer
            stosb
            mov al, ":"
            stosb
            mov al, "\"
            stosb
            mov al, 0
            stosb

            invoke SetCurrentDirectory,ADDR DrvBuffer  ; change drive
            invoke SendMessage,hWnd,WM_SETTEXT,0,ADDR DrvBuffer
            call ResetIt

        .elseif FileBuffer[1] == "."  ; Go back one directory
            szText BackOne,".."
            invoke SetCurrentDirectory,ADDR BackOne
            invoke GetCurrentDirectory,128,ADDR PathBuffer
            invoke SendMessage,hWnd,WM_SETTEXT,0,ADDR PathBuffer
            call ResetIt
        .else

        lea esi, FileBuffer
        lea edi, DirBuffer

      lpSt:
        lodsb
          cmp al, "["    ; strip left square bracket
          je @F
          cmp al, "]"    ; strip right square bracket
          je @F
          cmp al, 0      ; exit if zero
          je lpOut
        stosb
      @@:
        jmp lpSt
      lpOut:
        mov al, 0        ; append zero to DirBuffer
        stosb

        invoke GetCurrentDirectory,128,ADDR PathBuffer

        invoke lstrlen,ADDR PathBuffer
        mov fln, eax
        cmp fln, 3       ; 3 bytes long = root dir, don't append "\"
        je pBs

        invoke lstrcat,ADDR PathBuffer,ADDR BkSl
      pBs:
        invoke lstrcat,ADDR PathBuffer,ADDR DirBuffer
        invoke SetCurrentDirectory,ADDR PathBuffer
        invoke SendMessage,hWnd,WM_SETTEXT,0,ADDR PathBuffer
        call ResetIt

        .endif

    .else  ; Run selected file

        invoke GetCurrentDirectory,128,ADDR PathBuffer
        invoke lstrlen,ADDR PathBuffer
        mov fln, eax
        cmp fln, 3       ; 3 bytes long = root dir, don't append "\"
        je pBs2
        invoke lstrcat,ADDR PathBuffer,ADDR BkSl
      pBs2:
        invoke lstrcat,ADDR PathBuffer,ADDR FileBuffer
        invoke WinExec,ADDR PathBuffer,SW_NORMAL
        cmp eax, 31
        jg nOK

        jmp @F
          eMsg db "File must be EXE, COM, BAT or PIF",0
          eTit db "Incorrect file type was selected",0
        @@:

        invoke MessageBox,hWnd,ADDR eMsg,ADDR eTit,MB_OK

        nOK:

    .endif

    invoke SetFocus,hCtl
    
    ret
    
    ; ------------------------------

    ResetIt:
        invoke SendMessage,hCtl,LB_RESETCONTENT,0,0
        szText fpattern,"*.*"
        invoke SendMessage,hCtl,LB_DIR,
               DDL_DIRECTORY or DDL_DRIVES,ADDR fpattern
    ret

ListProc endp

; #########################################################################

end start
