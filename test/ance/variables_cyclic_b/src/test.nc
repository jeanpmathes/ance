// invalid

// Global variables are not allowed to have cyclic dependencies on themselves.

public a: i32 <: a;

public main () : u32
{
    return 0:32;
}

