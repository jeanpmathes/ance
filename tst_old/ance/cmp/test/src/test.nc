// valid

// Variables and functions can be declared as cmp (compile-time).
// This means they must be defined at compile-time and cannot be changed at runtime.
// In return, they can be used at compile-time.

private cmp x: u32 := 1:32;
private cmp y: u32 := x + 3:32 * 2:32;
private cmp z: u32 := foo() + 1:32;
private cmp w: u32 := bar(3:32);

// Compile-time functions are only evaluated at compile-time.

private cmp foo () : u32
{
    return x + y;
}

// Compile-time functions can have arguments, but they must be compile-time as well.

private cmp bar (a: u32) : u32
{
    return a + 1:32;
}

public main () : u32
{
    assert x == 1:32;
    assert y == 7:32;
    assert z == 9:32;
    assert w == 4:32;

    assert bar(x) == 2:32;
    assert bar(5:32) == 6:32;

    return 0:32;
}
