// valid
// o: "TTFFFT"

// For logical operations, the operators 'and' and 'or' can be used.
// Both operators are short-circuiting.

private std_out: Handle;

public define Handle alias ptr;

public main () :  u32
{
    std_out <: GetStdHandle(4294967285:32);

    assert true and true;
    assert true or false;
    assert false or true;

    // In these cases both expressions have to be evaluated:

    let b1 : bool <: get_true() and get_true();
    let b2 : bool <: get_false() or get_false();

    // In these cases only the first expression has to be evaluated:

    let b3 : bool <: get_false() and get_false();
    let b4 : bool <: get_true() or get_true();

    assert b1;
    assert not b2;
    assert not b3;
    assert b4;

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

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

private write (str: * u8, len:  u32) : void
{
    let written: * u32 <: new automatic  u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: * u8, nNumberOfBytesToWrite:  u32, lpNumberOfBytesWritten: * u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle:  u32) : Handle;
extern ExitProcess (uExitCode:  u32);
