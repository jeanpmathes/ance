// valid
// o: "Y"

// Variables can be redefined in the same scope they are defined.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let x : size <: 1;
    x <: 2;

    let x : *u8 <: c"X";
    x <: c"Y";

    write(x, 1:32);

    return 0:32;
}

private write (str: *u8, len: u32) : void
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
extern ExitProcess (uExitCode: u32);
