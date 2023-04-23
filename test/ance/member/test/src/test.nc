// valid
// o: "Hello, World!"

// Members of structs and other types can be accessed.

public struct String
{
    public str: *u8;
    public len: u32;
}

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let s: String;
    s str <: c"Hello, World!";
    s len <: 13:32;

    write(s);

    return 0:32;
}

private write (string: String) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, string str, string len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
