// invalid

// The members of structs must have unique names.

public struct Data
{
    public x: i32;
    public x: i32;
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