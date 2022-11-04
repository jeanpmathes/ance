// invalid

// The indirection operator is not define for every type.

public main () : u32
{
    let x: i64;
    x. <: 0:64; // The type i64 does not define indirection.

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
