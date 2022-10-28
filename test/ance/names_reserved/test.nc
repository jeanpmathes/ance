// valid

// In the core language, no names are reserved.

extern _start ();
extern _exit ();
extern _init ();

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
