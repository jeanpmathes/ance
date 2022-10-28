// valid

// The platform dependent size and diff type and their literals.

private s1: size <: 0:size;
private d1: diff <: +0:diff;

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
