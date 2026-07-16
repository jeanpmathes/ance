// invalid

// The indirection operator is not define for every type.

public main () : u32
{
    let x: s64;
    x. <: 0:64; // The type s64 does not define indirection.

    return 0:32;
}

