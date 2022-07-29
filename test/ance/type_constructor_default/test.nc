// valid

// Many basic types have a default constructor.

public main () : ui32
{
    let i: ui32; // Not specifying an assignment will cause the default constructor to be called.
    let j: ui32 <: ui32();

    // Both approaches produce the same value, but are not equivalent as the second includes a copy constructor call.
    assert i == j;

    let x1: S <: S();
    let x2: bool <: bool();

    return 0:32;
}

private struct S { }

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
