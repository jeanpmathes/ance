// valid
// o: "CCC"

// The language allows to use match-statements for control flow. These are similar to switch-cases.

private std_out: Handle;

public define Handle alias ptr;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    // Match statements are supported for all integer types.
    // These are fixed-width integers, size-types and integer pointers.
    // Additionally, boolean types are supported.

    let value: size <: 3;

    match value with
    {
        0:size => write(c"A", 1:32); // No break is required, because no fallthrough is possible.
        1:size => write(c"B", 1:32);
        2:size | 3:size => write(c"C", 1:32);
        4:size =>
        {
            write(c"D", 1:32);
        }
        default => write(c"E", 1:32);
    }

    let value: i32 <: 3;

    match value with
    {
        +0:32 => write(c"A", 1:32);
        +1:32 => write(c"B", 1:32);
        +2:32 | +3:32 => write(c"C", 1:32);
        +4:32 =>
        {
            write(c"D", 1:32);
        }
        default => write(c"E", 1:32);
    }

    let value: uiptr <: 0x3:uiptr;

    match value with
    {
        0x0:uiptr => write(c"A", 1:32);
        0x1:uiptr => write(c"B", 1:32);
        0x2:uiptr | 0x3:uiptr => write(c"C", 1:32);
        0x4:uiptr =>
        {
            write(c"D", 1:32);
        }
        default => write(c"E", 1:32);
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
