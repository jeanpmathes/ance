// invalid

// Every case of a match-statement must be unique.

private std_out: Handle;
private null_ptr: uiptr;

define bool as i1;
define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    let value: size <: 3;

    match value with
    {
        0 => write(c"A", 1:32);
        0 => write(c"B", 1:32); // Case 0 is already defined.
        default => write(c"C", 1:32);
    }

    return 0:32;
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