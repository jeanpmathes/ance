// invalid

// As defines can be used in any order, cyclic dependencies must be detected.

public define a alias b;
public define b alias c;
public define c alias a;

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
