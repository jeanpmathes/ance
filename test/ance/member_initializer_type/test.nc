// invalid

// The types of member initializers must match the types of the members.

public struct Invalid
{
    public member: u32 <: -1:64;
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
