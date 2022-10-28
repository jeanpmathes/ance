// invalid

// Structs cannot have cyclic type dependencies.

public struct Data1
{
    private d: Data2;
}

public struct Data2
{
    private d: Data1;
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
