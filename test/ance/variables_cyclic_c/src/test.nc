// invalid

// Global variables are not allowed to have cyclic dependencies trough functions.

public get_a () : i32 { return a; }
public get_b () : i32 { return b; }

public a: i32 <: get_b();
public b: i32 <: c;
public c: i32 <: get_a();

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
