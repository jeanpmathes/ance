// valid

// Bitwise operators are available for all integer types.

public main () : u32
{
    let x <: 0b00000001:8;
    let y <: 0b00000010:8;

    let r1 <: x <and> y;
    assert r1 == 0b00000000:8;

    let r2 <: x <or> y;
    assert r2 == 0b00000011:8;

    let r3 <: x <xor> y;
    assert r3 == 0b00000011:8;

    let r4 <: <not> x;
    assert r4 == 0b11111110:8;

    // Bitwise operators can also be applied to boolean values.
    // This is equivalent to a non-short-circuiting logical operator.

    let r5 <: true <and> false;
    assert r5 == false;

    let r6 <: true <or> false;
    assert r6 == true;

    let r7 <: true <xor> false;
    assert r7 == true;

    let r8 <: <not> true;
    assert r8 == false;

    return 0:32;
}

