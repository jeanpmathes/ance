// valid

// The platform dependent size and diff type and their literals.

private s1 : size <: 0:size;
private d1 : diff <: +0:diff;

// The number literals without type suffixes are of type size and diff.
private s2 : size <: 0;
private d2 : diff <: +0;
private d3 : diff <: -0;

public main () : ui32
{
    return 0:32;
}

public exit (exitcode : ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode : ui32);
