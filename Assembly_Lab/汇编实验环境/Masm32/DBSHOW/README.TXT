
DBMACROS.ASM & DBSHOW.DLL
~~~~~~~~~~~~~~~~~~~~~~~~~

DBSHOW.DLL is a dynamic link library that contains functions for displaying
DWORD size values in either a dialog box, the title bar or a status bar. It
is used in conjunction with a set of MACROS contained the file DBMACROS.ASM.

To use the DLL and MACROS while designing and testing an application, the
line, 

    include dbmacros.asm

should be added to the start of the file and the DLL should be in the SAME
directory as the application being developed.

Why use a DLL for services of this type ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
There are many places where a source code debugger is difficult and slow to
use. It is faster to get a single return value from a function by using a
set of services of this type and you have the option of different numerical
formats for display that are not available in a debugger.

There are currently five (5) function available in the DLL that are called
using the supplied macros.

How does it work ?
~~~~~~~~~~~~~~~~~~
The concept is very simple, the MACROS insert the necessary assembler code
to get the values and passes them to each function in the DLL for display
using the standard push parameter, call function syntax. You can easily see
how they work by reading the DBMACROS.ASM file.

----------------------------------------------------------------------------

 1. ShowReturn hWindow, value

    "hWindow" is a valid window handle
    "value" is the supplied DWORD value to be displayed

    The function called from this MACRO displays a dialog box with the
    value shown in Decimal, Hex and Binary.

    EXAMPLE
    invoke GetTickCount
    ShowReturn hWnd,eax

----------------------------------------------------------------------------

 2. UseTitleBar hWindow, value, dType

    "hWindow" is a valid window handle
    "value" is the supplied DWORD value to be displayed
    "dType" is the numeric format for display 1=decimal, 2=hex, 3=binary

    The function called by this MACRO displays the value in the format
    selected on the windows title bar. It can be used in places like a
    message loop for watching a value that changes at run time without
    interfering with the function of the program.

    EXAMPLE
        ---- WndProc Fragment ----

        .elseif uMsg == WM_SIZE
          UseTitleBar hWnd, lParam, 2

    This displays the lParam for WM_SIZE on the title bar in hex. When
    you size the window, the left four (4) hex characters show the client
    area width and the right four (4) hex characters show the client area
    height in hex.

----------------------------------------------------------------------------

 3. UseStatusBar hStatus, value, dType

    "hStatus" is a valid status bar window handle
    "value" is the supplied DWORD value to be displayed
    "dType" is the numeric format for display 1=decimal, 2=hex, 3=binary

    This can be used in exactly the same way as the "UseTitleBar" macro
    if the application has a status window.

----------------------------------------------------------------------------

 4. ShowRegisters hWindow, dType

    "hWindow" is a valid window handle
    "dType" is the numeric format for display 1=decimal, 2=hex, 3=binary

    This function call by the MACRO will display the

    eax, ebx, ecx, edx, esi, edi, ebp, esp registers at the point where

    the MACRO is called in any of the 3 different numerical formats.

----------------------------------------------------------------------------

5. ClockitStart
   ClockitStop hWindow,num

   "hWindow" is a valid window handle
   "num" is the format for display, 1=dialog box or 2=titlebar

   You use ClockitStart with no parameters at the point in your code
   that you wish to start the timing and ClockitStop at the point where
   you wish to stop the timing.

   EXAMPLE

   ClockitStart
   ;--------------------

    Do_Time_Critical_Code_Here

   ;--------------------
   ClockitStop hWnd,2

   This will display the duration of the code in milliseconds on the title
   bar.

   NOTE : With ring 3 access, there is a variation of 2 to 3 percent in
   the result which limits the usefulness when clocking very short duration
   code. It is also worth running the code multiple times to avoid the
   effects of caching.

----------------------------------------------------------------------------

    CREDIT

    The DLL and MACROS have been developed with the technical assistance
    of Iczelion to help programmers porting their skills across to writing
    in pure assembler.

----------------------------------------------------------------------------

    LICENCE

    The DLL and MACROS are available free of any charge whatsoever to any
    programmer who can use them. They retain the status of being private
    property and are not for sale or to be sold under any condition.

    DBMACROS.ASM & DBSHOW.DLL © Copyright S.L.Hutchesson 1998

    Steve Hutchesson < hutch@pbq.com.au >
    Sydney
    Australia