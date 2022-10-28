// invalid

// Variables defined in scopes hide outer variables. They also block access before definition.

public main () :  u32
{
    let x :  u32 <: 0:32;

    {
        x <: 1:32; // Not valid, because x will be defined later.
        let x :  u32 <: 1:32;
    }

    return x;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
