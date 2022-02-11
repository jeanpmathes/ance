// valid

// An assertion that has a correct condition.

public main () : ui32
{
    assert true;

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
