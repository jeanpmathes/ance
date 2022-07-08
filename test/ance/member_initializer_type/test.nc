// invalid

// The types of member initializers must match the types of the members.

public struct Invalid
{
    public member: ui32 <: -1:64;
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
