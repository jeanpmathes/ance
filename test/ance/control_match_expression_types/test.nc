// invalid

// In a match expression, all expression have to return the same type.

public main () : ui32
{
    let x: ui32 <: match 0:32 with
    {
        0:32 => 0:32,
        1:32 => 1:64, // Provides incorrect type.
        2:32 => 2:32,
        default => 3:32
    };

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
