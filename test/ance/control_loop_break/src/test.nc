// invalid

// The break-statement must be used in a loop body.

public main () : u32
{
    break;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
