// valid
// o: "TTFFFT"

// For logical operations, the operators 'and' and 'or' can be used.
// Both operators are short-circuiting.

private std_out: Handle;
private null_ptr: uiptr;

define Handle as *void;

public main () : ui32
{
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
