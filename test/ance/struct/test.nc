// valid

// The language allows to define structs, which hold together values.

public define DataAlias alias Data;
public define DataClone as Data;

public struct Data
{
    public x1: i32;
    private x2: [Vector3s; 3];
    private x3: Vector3s;
    private x4: *Data;
    private x5: *DataAlias;
    private x6: *DataClone;
}

private struct Vector3s
{
    public x: single;
    public y: single;
    public z: single;
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
