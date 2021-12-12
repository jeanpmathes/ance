// valid
// o: "ABC"

// Memory allocation mechanisms.

private std_out : Handle;
private null_ptr : uiptr;

define bool as i1;
define Handle as *void;

// Defined functions must be public or private.

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    // Dynamic memory is allocated using new.
    let str : *ui8 <: new[3] dynamic ui8;

    str[0] <: 'A';
    str[1] <: 'B';
    str[2] <: 'C';

    write(str, 3:32);

    // Dynamically allocated memory must be freed using delete.
    delete str;

    return 0:32;
}

// The void return type can be omitted.

public exit (exitcode : ui32)
{
    ExitProcess(exitcode);
}

private write (str : *ui8, len : ui32) : void
{
    let written : *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

// Functions can be declared as extern.

extern WriteFile (hFile : Handle, lpBuffer : *ui8, nNumberOfBytesToWrite : ui32, lpNumberOfBytesWritten : *ui32, lpOverlapped : uiptr);
extern GetStdHandle (nStdHandle : ui32) : Handle;
extern ExitProcess (uExitCode : ui32);