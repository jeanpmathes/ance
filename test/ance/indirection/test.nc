// valid

// The indirection operator allows to dereference a pointer.

public struct Point
{
    public x: i64;
    public y: i64;
}

public main () : u32
{
    let value: Point;
    value x <: 1;
    value y <: 2;

    let value_ptr: *Point <: addressof value;
    value_ptr.x <: -1;
    value_ptr.y <: -2;

    assert value x == -1:64;
    assert value y == -2:64;

    assert -1:64 == value_ptr.x;
    assert -2:64 == value_ptr.y;

    let another_value: Point;
    another_value x <: 3;
    another_value y <: 4;

    // With the indirection operator, the value pointed to can both be read or written.
    value_ptr. <: another_value;

    assert value x == +3:64;
    assert value y == +4:64;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
