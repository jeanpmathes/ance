// valid

// The type of local variable is not required to be declared explicitly.

public define ONE alias u8;
public define TWO alias u16;
public define FOUR alias u32;

public main () : u32
{
    let x <: 1;
    let y <: "2";

    let v1 <: 1:8;
    assert sizeof(v1) == sizeof ONE;

    let v2 <: 1:16;
    assert sizeof(v2) == sizeof TWO;

    let v3 <: 1:32;
    assert sizeof(v3) == sizeof FOUR;

    let v4 <: if true then v1 else v2;
    assert sizeof(v4) == sizeof TWO;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
