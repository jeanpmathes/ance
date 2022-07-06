// invalid

// Structs cannot hold values of their own type, even if the type is an alias or clone.

public define DataAlias alias Data;
public define DataClone as Data;

public struct Data
{
    private a: DataAlias;
    private c: DataClone;
}

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
