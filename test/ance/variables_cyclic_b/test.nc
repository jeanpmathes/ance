// invalid

// Global variables are not allowed to have cyclic dependencies on themselves.

public a: i32 <: a;

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
