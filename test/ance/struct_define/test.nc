// invalid

// Structs cannot hold values of their own type, even if the type is an alias or clone.

public define DataAlias alias Data;

public struct Data
{
    private a: DataAlias;
}

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
