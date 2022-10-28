// valid
// o: "ABC"

// Memory allocation mechanisms.

private std_out: Handle;

public define Handle alias ptr;

public main () :  u32
{
    std_out <: GetStdHandle(4294967285:32);

    // Dynamic memory is allocated using new.
    let ptr_to_int: *i32 <: new dynamic i32;

    // Dynamically allocated memory must be freed using delete.
    delete ptr_to_int;

    // Allocating buffers returns a buffer-pointer.
    let str: [] u8 <: new[3] dynamic  u8;

    str[0] <: 8'A';
    str[1] <: 8'B';
    str[2] <: 8'C';

    write(str, 3:32);

    // Buffers must be freed using delete[].
    delete[] str;

    return 0:32;
}

// The void return type can be omitted.

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

private write (str: [] u8, len:  u32) : void
{
    let written: * u32 <: new automatic  u32;
    WriteFile(std_out, str, len, written, null);
}

// Functions can be declared as extern.

extern WriteFile (hFile: Handle, lpBuffer: [] u8, nNumberOfBytesToWrite:  u32, lpNumberOfBytesWritten: * u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle:  u32) : Handle;
extern ExitProcess (uExitCode:  u32);
