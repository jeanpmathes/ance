// invalid

// Structs cannot hold values of their own type.

public struct Data
{
    private d: Data;
}

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
