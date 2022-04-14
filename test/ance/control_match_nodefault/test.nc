// valid
// o: "true"

// Match-statements do not need a default case.

private std_out: Handle;
private null_ptr: uiptr;

define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    let value: bool <: true;

    match value with
    {
        false => write(c"false", 5:32);
        true => write(c"true", 4:32);
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
