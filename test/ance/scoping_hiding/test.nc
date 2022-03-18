// valid

// Variables defined in scopes hide outer variables. They also block access before definition.

public main () : ui32
{
    let x : ui32 <: 0:32;

    {
        x <: 1:32; // Not valid, because x will be defined later.
        let x : ui32 <: 1:32;
    }

    return x;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
