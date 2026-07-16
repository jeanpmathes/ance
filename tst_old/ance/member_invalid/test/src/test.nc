// invalid

// Only existing members can be accessed.

public struct Data
{
    private x: s32;
}

public main () : u32
{
    let d: Data;

    // The member accesses here are not allowed as the members do not exist.
    d y <: 10;

    return 0:32;
}

