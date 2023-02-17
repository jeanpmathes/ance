// valid
// o: "AAA"

// In a while-loop, a continue statement will skip the rest of the loop body and continue with the next iteration.

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    let count: size <: 0;

    while count < 4 do
    {
        count <: count + 1;

        // The continue can be nested in a block.
        {
            if count == 3 then continue;
        }

        write(c"A", 1:32);
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
