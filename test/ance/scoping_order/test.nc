// invalid

// Variables can only be accessed after they have been defined.

public main () : u32
{
    {
        x <: 1:32; // Not valid, because x is not defined.
    }

    let x : u32 <: 0:32;

    return x;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
