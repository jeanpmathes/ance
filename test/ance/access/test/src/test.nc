// invalid

// Public definitions are not allowed to export private definitions.

private define PrivateType alias u32;

public foo (x : PrivateType) : u32 // Not allowed.
{
    return x;
}

public main () : u32
{
    return 0:32;
}

