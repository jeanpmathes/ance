// valid

// For logical operations, the not operator can be used.

public main () : ui32
{
    assert not false;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
