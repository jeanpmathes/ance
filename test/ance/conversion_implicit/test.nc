// valid

// Integer and float types allow implicit conversion of their values to larger types.

public define int alias i64;

public main () : ui32
{
    let x1: i32 <: +1:16;
    let x2: i64 <: -1:32;

    assert x2 == -1:64;

    let x3: ui182 <: 1:64;
    let x4: ui3 <: 1:2;

    // Unsigned values can be implicitly converted to signed values of larger size.

    let x5: i32 <: 1:31;
    let x6: i64 <: 1:63;

    assert x6 == +1:64;

    let x7: half <: 1.0h;
    let x8: single <: x7;
    let x9: double <: x8;
    let x10: quad <: x9;

    assert x10 == 1.0q;

    let x11: size <: 15;
    let x12: diff <: x11;

    // Type aliasing has no effect on implicit conversion.
    let x13: int <: x4;
    let x14: i64 <: x13;

    return 0:32;
}

private get_quad() : quad
{
    // The return statement also allows implicit conversion of its value.
    return 1.0h;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
