// invalid

// Every overload must have a unique signature.

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);

extern overloaded (x:  u32);
extern overloaded (y:  u32);
