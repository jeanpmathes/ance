// invalid

// The members of structs must have unique names.

public struct Data
{
    public x: i32;
    public x: i32;
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
