// invalid

// Global variables are not allowed to have cyclic dependencies on each other.

public a: s32 <: b;
public b: s32 <: a;

public main () : u32
{
    return 0:32;
}

