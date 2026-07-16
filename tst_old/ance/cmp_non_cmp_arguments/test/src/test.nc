// invalid

// Arguments to a cmp-function must be available at compile-time.

private cmp foo (a : u32) {}

public main () : u32
{
    let x: u32 := 0:32;
    foo(x); // Invalid, as x is not available at compile-time.

    return 0:32;
}
