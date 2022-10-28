// valid
// o: "C"

// To select a value, match-expressions can be used.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let value: size <: 3;

    let string: *u8 <: match value with
    {
        0:size => c"A",
        1:size => c"B",
        2:size | 3:size => c"C",
        4:size => c"D",
        default => c"E"
    };

    write(string, 1:32);

    return 0:32;
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
