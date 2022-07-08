// invalid

// Pointers cannot point to types that are not defined.

struct Data
{
    private p: *Undefined;
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
