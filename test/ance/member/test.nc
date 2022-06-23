// valid
// o: "Hello, World!"

// Members of structs and other types can be accessed.

public struct String
{
    public str: *ui8;
    public len: ui32;
}

private std_out: Handle;
private null_ptr: uiptr;

define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    let s: String;
    s str <: c"Hello, World!";
    s len <: 13:32;

    write(s);

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private write (string: String) : void
{
    let written: *ui32 <: new automatic ui32;
    WriteFile(std_out, string str, string len, written, null_ptr);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: uiptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
