// invalid

// Structs cannot have circular type dependencies.

public struct Data1
{
    private d: Data2;
}

public struct Data2
{
    private d: Data1;
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
