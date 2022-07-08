// invalid

// Structs cannot hold values of their own type.

public struct Data
{
    private d: Data;
}

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
