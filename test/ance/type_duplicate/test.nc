// invalid

// Type names must be unique.

public struct Duplicate {}
public define Duplicate as i32;

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
