// valid
// o: "A"

// In a while-loop, a break statement will cause the loop to exit immediately.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let count: size <: 0;

    while count < 4 do
    {
        count <: count + 1;

        let inner_count: size <: 0;

        while inner_count < 4 do
        {
            inner_count <: inner_count + 1;

            if inner_count == 2 then break;

            write(c"A", 1:32);
        }

        if count == 1 then break;
    }

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
