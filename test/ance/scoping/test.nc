// valid

// In function scopes, more anonymous scopes can be defined.

public main () : ui32
{
    let x : ui32 <: 0:32;

    {
        let x : ui32 <: 1:32;
    }

    return x;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
