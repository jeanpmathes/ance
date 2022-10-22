// valid

// In the core language, no names are reserved.

extern _start ();
extern _exit ();
extern _init ();

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
