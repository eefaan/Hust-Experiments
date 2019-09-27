; #########################################################################

      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive

; #########################################################################

      include \masm32\include\windows.inc
      include \masm32\include\user32.inc
      include \masm32\include\kernel32.inc

      includelib \masm32\lib\user32.lib
      includelib \masm32\lib\kernel32.lib

; #########################################################################

    .code

start:

        invoke ExitWindowsEx,1,0
        invoke ExitProcess,eax

; #########################################################################

end start

        ; Flags for ExitWindowEx

        ; EWX_LOGOFF    equ 0
        ; EWX_SHUTDOWN  equ 1
        ; EWX_REBOOT    equ 2
        ; EWX_FORCE     equ 4
        ; EWX_POWEROFF  equ 8













