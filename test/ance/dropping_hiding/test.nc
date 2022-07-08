// invalid

// A hidden variable cannot be unhidden by dropping the hiding variable.

public main () : ui32
{
    let x: size <: 15;

    {
        // The outer x is hidden in this scope.

        let x: single <: 0.0s;
        drop x;

        let z: size <: x; // Will not compile.
    }

    let z: size <: x;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
