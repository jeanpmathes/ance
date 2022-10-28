// invalid

// The maximum size of integers is 2^22, so 4194305 is not a valid integer size.

private x1: i65537;

public main () : u32
{
    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
