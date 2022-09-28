// valid
// o: "AD"

// The language allows to use if-else-statements for control flow.

private std_out: Handle;

public define Handle alias ptr;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    if 12 == 12 then write(c"A", 1:32);

    if 12 == 14 then
    {
        write(c"B", 1:32);
    }
    else if 13 == 14 then
    {
        write(c"C", 1:32);
    }
    else
    {
        write(c"D", 1:32);
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
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
