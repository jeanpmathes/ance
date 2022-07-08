// valid

// Each struct member can be given a value it is initialized to.

private struct Values
{
    public a: i32 <: +15:32;
    public b: *ui8 <: c"A";
    public c: bool;
}

public main () : ui32
{
    let v: Values; // Struct members are initialized here.

    assert v a == +15:32;
    assert v b[0] == 'A';
    assert not v c;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
