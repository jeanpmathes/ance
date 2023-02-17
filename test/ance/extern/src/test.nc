// valid

// Calling C-API functions and providing functions callable from C are both supported.

public main () : u32
{
    return 0:32;
}

// Extern functions without code take their definition from linked libraries.

// Extern functions with code can be called and linked from other libraries.
extern test (a: u32, b: u32) : u32
{
    return a + b;
}
