// valid
// o: "ABCDE"

// The language supports function overloading.

private std_out: Handle;
private null_ptr: uiptr;

define bool as i1;
define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    overloaded();
    overloaded(0:32);
    overloaded(0:64);
    overloaded(0:32, 0:32);

    // Overload resolution considers implicit conversions.
    overloaded(0.2h);

    return 0:32;
}

// The void return type can be omitted.

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private write (str: *ui8, len: ui32) : void
{
    let written: *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

public overloaded ()
{
    write(c"A", 1:32);
}

private overloaded (x: ui32)
{
    write(c"B", 1:32);
}

private overloaded (x: ui64)
{
    write(c"C", 1:32);
}

private overloaded (x: ui32, y: ui32)
{
    write(c"D", 1:32);
}

private overloaded (x: single)
{
    write(c"E", 1:32);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: uiptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
