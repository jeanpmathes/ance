// valid

// The sizeof expressions allow to get the size of a type.

public main () : u32
{
    // Two variants of the expression exist, one for types and one for the types returned by an expression.
    // Both variants return a value of type size.

    // The variant for types:

    let s1: size <: sizeof u8;
    assert s1 == 1;

    // The variant for expressions:
    let x: s32;
    let s2: size <: sizeof(x);
    assert s2 == 4;

    // The size of unit is zero.
    assert sizeof () == 0;

    return 0:32;
}

