; ##########################################################################

;                        MACROS for using Dbshow.dll

; ##########################################################################

      ShowReturn MACRO hWindow, value
        LOCAL lbl
        LOCAL LibName
        LOCAL ProcName
        jmp lbl
          LibName       db "Dbshow.dll",0
          ProcName      db "ShowReturnValue",0
        lbl:
          push value
          push hWindow
          invoke LoadLibrary,ADDR LibName
          invoke GetProcAddress,eax,ADDR ProcName
          call eax
        ENDM

; ##########################################################################

      UseTitleBar MACRO hWindow, value, dType
        LOCAL lbl
        LOCAL LibName
        LOCAL ProcName
        jmp lbl
          LibName       db "Dbshow.dll",0
          ProcName      db "UseTitleBar",0
        lbl:
          push dType
          push value
          push hWindow
          invoke LoadLibrary,ADDR LibName
          invoke GetProcAddress,eax,ADDR ProcName
          call eax
        ENDM

; ##########################################################################

      UseStatusBar MACRO hWindow, value, dType
        LOCAL lbl
        LOCAL LibName
        LOCAL ProcName
        jmp lbl
          LibName       db "Dbshow.dll",0
          ProcName      db "UseStatusBar",0
        lbl:
          push dType
          push value
          push hWindow
          invoke LoadLibrary,ADDR LibName
          invoke GetProcAddress,eax,ADDR ProcName
          call eax
        ENDM

; ##########################################################################

      ShowRegisters MACRO hWindow, dType
        LOCAL lbl
        LOCAL LibName
        LOCAL ProcName
        jmp lbl
          LibName       db "Dbshow.dll",0
          ProcName      db "ShowRegisters",0
        lbl:
          push dType
          push esp
          push ebp
          push edi
          push esi
          push edx
          push ecx
          push ebx
          push eax
          push hWindow
        invoke LoadLibrary,ADDR LibName
        invoke GetProcAddress,eax,ADDR ProcName
        call eax
      ENDM

; ##########################################################################

      ClockitStart MACRO
        invoke GetTickCount
        push eax
      ENDM

; ##########################################################################

      ClockitStop MACRO hWind,num
        LOCAL lbl
        LOCAL LibName
        LOCAL ProcName

        invoke GetTickCount
        pop edx
        sub eax, edx

        jmp lblz
          LibName   db "Dbshow.dll",0
          ProcName  db "StopClockMs",0
        lblz:

        mov edx,num

        push edx
        push eax
        push hWind
        invoke LoadLibrary,ADDR LibName
        invoke GetProcAddress,eax,ADDR ProcName
        call eax
      ENDM

; ##########################################################################