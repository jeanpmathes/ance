// invalid

// As defines can be used in any order, cyclic dependencies must be detected.

public define a alias b;
public define b alias c;
public define c alias a;

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
