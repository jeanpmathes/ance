// invalid

// Argument names must be unique.

public foo (a: u32, a: u32) : u32
{
    return a;
}

public main () : u32
{
    return foo(0:32, 0:32);
}

