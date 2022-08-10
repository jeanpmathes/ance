// valid
// o: "Y"

// Variables can be redefined in the same scope they are defined.

private std_out: Handle;
private null_ptr: uiptr;

public define Handle alias *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    let x : size <: 1;
    x <: 2;

    let x : *ui8 <: c"X";
    x <: c"Y";

    write(x, 1:32);

    return 0:32;
}

private write (str: *ui8, len: ui32) : void
{
    let written: *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: uiptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
