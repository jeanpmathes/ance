// invalid

// Match-statements must complete cover all possible cases.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let value: size <: 3;

    match value with
    {
        0:size => write(c"A", 1:32); // Only one case covered.
    }

    return 0:32;
}

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
