// valid
// o: "TF"

// Instead of using if-statements, if-expression can be used too.

private std_out: Handle;
private null_ptr: uiptr;

define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    let b : bool <: true;

    // Only the expression that will actually provide the value is evaluated.

    b <: if true then get_true() else get_false();
    b <: if false then get_true() else get_false();

    return 0:32;
}

private get_true () : bool
{
    write(c"T", 1:32);
    return true;
}

private get_false () : bool
{
    write(c"F", 1:32);
    return false;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private write (str: *ui8, len: ui32) : void
{
    let written: *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: uiptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
