// invalid

// In the global scope and other unordered scopes, every name can be used at most once.

public nameA () {}
public nameA: i32;

public nameB: i32;
define nameB alias i32;

public struct nameC {}
public nameC () {}

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
