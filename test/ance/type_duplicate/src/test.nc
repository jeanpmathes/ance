// invalid

// Type names must be unique.

public struct Duplicate {}
public define Duplicate alias i32;

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
