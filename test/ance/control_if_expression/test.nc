// valid
// o: "TF"

// Instead of using if-statements, if-expression can be used too.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
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

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
extern ExitProcess (uExitCode: u32);
