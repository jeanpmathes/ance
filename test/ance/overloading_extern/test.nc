// invalid

// Extern functions cannot be overloaded with other extern functions.

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);

extern overloaded ();
extern overloaded (x:  u32);