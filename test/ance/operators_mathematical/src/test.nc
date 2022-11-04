// valid

// The basic mathematical operators.

public main () : u32
{
    // All mathematical operators are supported for all fixed-width integer types.

    let a1: i32 <: +5:32;
    let b1: i32 <: -5:32;

    let x1: i32 <: a1 + b1;
    let x2: i32 <: a1 - b1;
    let x3: i32 <: a1 * b1;
    let x4: i32 <: a1 / b1;
    let x5: i32 <: a1 % b1;

    // All mathematical operators are supported for all floating-point types.

    let a2: single <: +5.0s;
    let b2: single <: -5.0s;

    let x6: single <: a2 + b2;
    let x7: single <: a2 - b2;
    let x8: single <: a2 * b2;
    let x9: single <: a2 / b2;
    let x10: single <: a2 % b2;

    let x11: half <: 1.0h + 2.0h;
    let x12: single <: 1.0s + 2.0s;
    let x13: double <: 1.0d + 2.0d;
    let x14: quad <: 1.0q + 2.0q;

    // All mathematical operators are supported for the size and diff type.

    let a3: size <: 5;
    let b3: size <: 5;

    let x15: size <: a3 + b3;
    let x16: size <: a3 - b3;
    let x17: size <: a3 * b3;
    let x18: size <: a3 / b3;
    let x19: size <: a3 % b3;

    let a4: diff <: +5;
    let b4: diff <: -5;

    let x20: diff <: a4 + b4;
    let x21: diff <: a4 - b4;
    let x22: diff <: a4 * b4;
    let x23: diff <: a4 / b4;
    let x24: diff <: a4 % b4;

    // All mathematical operators are supported for the uiptr type.

    let a5: uiptr <: 0x01:uiptr;
    let b5: uiptr <: 0x02:uiptr;

    let x25: uiptr <: a5 + b5;
    let x26: uiptr <: a5 - b5;
    let x27: uiptr <: a5 * b5;
    let x28: uiptr <: a5 / b5;
    let x29: uiptr <: a5 % b5;

    // Signed values can be negated.

    let x30: i32 <: -a1;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
