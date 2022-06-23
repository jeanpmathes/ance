// invalid

// The members of structs can be protected using the access modifiers.

public struct Data
{
    private x: i32;
    private y: i32;
}

public main () : ui32
{
    let d: Data;

    // The member accesses here are not allowed as the members are private.

    d x <: 10;
    d y <: d x;

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
