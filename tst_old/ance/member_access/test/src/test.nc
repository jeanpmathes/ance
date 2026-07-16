// invalid

// The members of structs can be protected using the access modifiers.

public struct Data
{
    private x: s32;
    private y: s32;
}

public main () : u32
{
    let d: Data;

    // The member accesses here are not allowed as the members are private.

    d x <: 10;
    d y <: d x;

    return 0:32;
}

