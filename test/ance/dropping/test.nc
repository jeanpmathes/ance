// valid

// Variables can be dropped in the scope that they are declared in.

public main () : ui32
{
    let x: size <: 15;
    let y: size <: x;

    drop x;

    // x cannot be used here, because it has been dropped.

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);