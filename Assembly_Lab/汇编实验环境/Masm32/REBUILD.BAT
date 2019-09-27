: -----------------------------------------------------------------------
: This batch file builds the INCLUDE files in the INCLUDE directory from
: the standard libraries in the LIB directory. It then changes to the
: M32LIB directory and builds the MASM32 library and copied it to the LIB
: directory and copies the MASM32.INC file to the INCLUDE directory.
: -----------------------------------------------------------------------

@echo off
cd include
l2inca /M ..\lib\*.lib
cd..\m32lib
copy masm32.inc \masm32\include\masm32.inc
\masm32\bin\ml /c /coff *.asm
\masm32\bin\lib *.obj /out:masm32.lib
copy masm32.lib \masm32\lib\masm32.lib
del *.obj
cd ..
