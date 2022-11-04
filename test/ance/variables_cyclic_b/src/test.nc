// invalid

// Global variables are not allowed to have cyclic dependencies on themselves.

public a: i32 <: a;

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
