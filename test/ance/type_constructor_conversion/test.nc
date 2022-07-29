// valid

// Constructors can be used for conversions when there could be a loss of information.

public main () : ui32
{
    let i: size <: 12;
    let j: ui32 <: ui32(a);
    let k: size <: size(b);

    let f1: single <: 12.0s;
    let f2: double <: f1;
    let f3: single <: single(f2);

    let b1: bool <: true;
    let b2: i1 <: i1(b1);
    let b3: bool <: bool(b2);

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
