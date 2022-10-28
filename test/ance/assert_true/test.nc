// valid

// An assertion that has a correct condition.

public main () : u32
{
    assert true;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
