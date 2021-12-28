// valid
// o: "x"

// The basic mathematical operators.

private std_out : Handle;
private null_ptr : uiptr;

define bool as i1;
define Handle as *void;

public main () : ui32
{
    std_out <: GetStdHandle(4294967285:32);

    // All mathematical operators are supported for all integer types.

    let a1 : i32 <: +5:32;
    let b1 : i32 <: -5:32;

    let x1 : i32 <: a1 + b1;
    let x2 : i32 <: a1 - b1;
    let x3 : i32 <: a1 * b1;
    let x4 : i32 <: a1 / b1;
    let x5 : i32 <: a1 % b1;

    // Most mathematical operators are supported for all floating-point types.

    let a2 : single <: +5.0s;
    let b2 : single <: -5.0s;

    let x6 : single <: a2 + b2;
    let x7 : single <: a2 - b2;
    let x8 : single <: a2 * b2;
    let x9 : single <: a2 / b2;

    let x10 : half <: 1.0h + 2.0h;
    let x11 : single <: 1.0s + 2.0s;
    let x12 : double <: 1.0d + 2.0d;
    let x13 : quad <: 1.0q + 2.0q;

    // All mathematical operators are supported for the size and diff type.

    let a3 : size <: 5;
    let b3 : size <: 5;

    let x14 : size <: a3 + b3;
    let x15 : size <: a3 - b3;
    let x16 : size <: a3 * b3;
    let x17 : size <: a3 / b3;
    let x18 : size <: a3 % b3;

    let a4 : diff <: +5;
    let b4 : diff <: -5;

    let x19 : diff <: a4 + b4;
    let x20 : diff <: a4 - b4;
    let x21 : diff <: a4 * b4;
    let x22 : diff <: a4 / b4;
    let x23 : diff <: a4 % b4;

    return 0:32;
}

public exit (exitcode : ui32)
{
    ExitProcess(exitcode);
}

private write (str : *ui8, len : ui32) : void
{
    let written : *ui32 <: new automatic ui32;
    WriteFile(std_out, str, len, written, null_ptr);
}

extern WriteFile (hFile : Handle, lpBuffer : *ui8, nNumberOfBytesToWrite : ui32, lpNumberOfBytesWritten : *ui32, lpOverlapped : uiptr);
extern GetStdHandle (nStdHandle : ui32) : Handle;
extern ExitProcess (uExitCode : ui32);
