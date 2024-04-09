// valid

// Integer and float types allow implicit conversion of their values to larger types.

public define int alias s64;

public main () : u32
{
    let x1: s32 <: +1:16;
    let x2: s64 <: -1:32;

    assert x2 == -1:64;

    let x3: u182 <: 1:64;
    let x4: u3 <: 1:2;

    // Unsigned values can be implicitly converted to signed values of larger size.

    let x5: s32 <: 1:31;
    let x6: s64 <: 1:63;

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
    let x14: s64 <: x13;

    return 0:32;
}

private get_quad() : quad
{
    // The return statement also allows implicit conversion of its value.
    return 1.0h;
}

