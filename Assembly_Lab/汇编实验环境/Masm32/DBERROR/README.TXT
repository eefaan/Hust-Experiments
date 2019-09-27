MASM32 debugging DLL

The two following file are used together to display the return value of a
call to the API GetLastError().

    dberror.dll     31744 bytes
    errormac.asm    1005  bytes

To use them in a program where you need to test an error returned by
GetLastError(), you must put them in the same directory as the file that
has the return value needing to be tested. All that needs to be done in
the source file is to include the macro file with,

    include errormac.asm

and after the function that need to have its error condition checked,

    ShowLastError

The result is the string defined in winerror.h for the error that has
occurred and it is displayed in a dialog box.

EXAMPLE
  ; ------------------------------------
  ; The function that needs to be tested
  ; ------------------------------------
    invoke TheAPIFunction, parameters etc
    ShowLastError

It is important that the macro ShowLastError is placed directly after the
function that is being tested. If it is put later after other code, it will
not get the correct error number returned by the failed function.

----------------------------------------------------------------------------

The two (2) files errormac.asm and dberror.dll are available to any
programmer who can finds a use for them without any form of charge
whatsoever. 

The two files errormac.asm and dberror.dll are copyright software that are
not for sale and not to be sold or included in any commercial package.

They both retain the status of being private property and have not and will
not be placed in the public domain.

Steve Hutchesson < hutch@pbq.com.au > 1999.

----------------------------------------------------------------------------