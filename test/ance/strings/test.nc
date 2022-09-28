// valid
// o: "ABC\0"

// There are multiple types of string literals.

// Char array literals create an array that contains the specified characters.

private str1: [ui8; 0] <: "";
private str2: [ui8; 1] <: "A";
private str3: [ui8; 2] <: "AB";
private str4: [ui8; 3] <: "ABC";

// C-style string literals contain a pointer to a null-terminated char sequence.

private str5: *ui8 <: c"";
private str6: *ui8 <: c"A";
private str7: *ui8 <: c"AB";
private str8: *ui8 <: c"ABC";

private std_out: Handle;
private null_ptr: uiptr;

public define Handle alias ptr;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    write(str8, 4:32);

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private write (str: *ui8, len: ui32)
{
    let written: *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

extern WriteFile (hFile: Handle, lpBuffer: *ui8, nNumberOfBytesToWrite: ui32, lpNumberOfBytesWritten: *ui32, lpOverlapped: uiptr);
extern GetStdHandle (nStdHandle: ui32) : Handle;
extern ExitProcess (uExitCode: ui32);
