// valid
// o: "AD"

// The language allows to use if-else-statements for control flow.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
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

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
