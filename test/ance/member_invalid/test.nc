// invalid

// Only existing members can be accessed.

public struct Data
{
    private x: i32;
}

public main () : ui32
{
    let d: Data;

    // The member accesses here are not allowed as the members do not exist.
    d y <: 10;

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
