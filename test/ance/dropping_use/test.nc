// invalid

// A variable that has been dropped cannot be used.

public main () : ui32
{
    let x: size <: 15;
    let y: size <: x;

    drop x;

    let z: size <: x; // Will not compile.

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
