// invalid

// Structs cannot hold values of their own type, even if the type is an alias or clone.

define DataAlias alias Data;
define DataClone as Data;

struct Data
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
