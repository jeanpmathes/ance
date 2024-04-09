// valid

// The language allows to define structs, which hold together values.

public define DataAlias alias Data;

public struct Data
{
    public x1: s32;
    private x2: [Vector3s; 3];
    private x3: Vector3s;
    private x4: *Data;
    private x5: *DataAlias;
}

private struct Vector3s
{
    public x: single;
    public y: single;
    public z: single;
}

public main () : u32
{
    return 0:32;
}

