// invalid

// A variable can only be dropped in the same scope it was declared in.

public main () : ui32
{
    let x: size <: 15;

    {
        drop x; // Will not compile.
    }

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
