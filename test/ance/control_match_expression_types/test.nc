// invalid

// In a match expression, all expression have to return the same type.

public main () :  u32
{
    let x:  u32 <: match 0:32 with
    {
        0:32 => 0:32,
        1:32 => 1:64, // Provides incorrect type.
        2:32 => 2:32,
        default => 3:32
    };

    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
