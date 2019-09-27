@echo off
\masm32\bin\ml /c /coff /Cp skeleton.asm
\masm32\bin\link /DLL /DEF:skeleton.def /SUBSYSTEM:WINDOWS /LIBPATH:\masm32\lib skeleton.obj
pause