// invalid

// Pointers cannot point to types that are not defined.

struct Data
{
    private p: *Undefined;
}

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
