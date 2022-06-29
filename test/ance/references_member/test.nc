// valid

// References permit accessing a member just as if the referenced variable would be used.

public struct Data
{
    public x: i64;
    public y: i64;
}

public main () : ui32
{
    let d: Data;
    d x <: 1;

    let d_ref: &Data ref d;
    d_ref x <: 2;

    assert d x == +2:64;

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
