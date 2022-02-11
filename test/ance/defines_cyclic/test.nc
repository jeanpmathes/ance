// invalid

// As defines can be used in any order, cyclic dependencies must be detected.

define a as b;
define b as c;
define c as a;

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
