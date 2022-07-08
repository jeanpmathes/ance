// invalid

// Variables can only be accessed after they have been defined.

public main () : ui32
{
    {
        x <: 1:32; // Not valid, because x is not defined.
    }

    let x : ui32 <: 0:32;

    return x;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
