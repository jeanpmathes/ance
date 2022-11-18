// invalid

// The continue-statement must be used in a loop body.

public main () : u32
{
    continue;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
