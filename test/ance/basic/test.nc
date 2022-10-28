// valid
// o: "Hello, World!"

// A simple hello world program using the Windows API.

private std_out: Handle;

public define Handle alias ptr;

// Defined functions must be public or private.

public main () :  u32
{
    std_out <: GetStdHandle(4294967285:32);

    write(c"Hello, World!", 13:32);

    return 0:32;
}

// The void return type can be omitted.

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

private write (str: * u8, len:  u32) : void
{
    let written: * u32 <: new automatic  u32;
    WriteFile(std_out, str, len, written, null);
}

// Functions can be declared as extern.

extern WriteFile (hFile: Handle, lpBuffer: * u8, nNumberOfBytesToWrite:  u32, lpNumberOfBytesWritten: * u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle:  u32) : Handle;
extern ExitProcess (uExitCode:  u32);
