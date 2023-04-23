// valid
// o: "CCC"

// The language allows to use match-statements for control flow. These are similar to switch-cases.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
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

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
