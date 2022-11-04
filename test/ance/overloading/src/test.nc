// valid
// o: "ABCDE"

// The language supports function overloading.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
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

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

public overloaded ()
{
    write(c"A", 1:32);
}

private overloaded (x: u32)
{
    write(c"B", 1:32);
}

private overloaded (x: u64)
{
    write(c"C", 1:32);
}

private overloaded (x: u32, y: u32)
{
    write(c"D", 1:32);
}

private overloaded (x: single)
{
    write(c"E", 1:32);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
extern ExitProcess (uExitCode: u32);
