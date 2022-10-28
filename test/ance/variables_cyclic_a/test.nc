// invalid

// Global variables are not allowed to have cyclic dependencies on each other.

public a: i32 <: b;
public b: i32 <: a;

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
