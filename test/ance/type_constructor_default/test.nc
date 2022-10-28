// valid

// Many basic types have a default constructor.

public main () :  u32
{
    let i:  u32; // Not specifying an assignment will cause the default constructor to be called.
    let j:  u32 <:  u32();

    // Both approaches produce the same value, but are not equivalent as the second includes a copy constructor call.
    assert i == j;

    let x1: S <: S();
    let x2: bool <: bool();

    return 0:32;
}

private struct S { }

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
