// valid

// Vector types can be used to perform operations on a vector of values.

public struct Data
{
    public x: uiptr;
    public y: [*i8; 3];
    public z: single;
}

public main () : u32
{
    // A vector type consists of element type and element count.
    // A vector literal is a list of elements and optionally the vector type.

    let x <: <i32 | 1, 2, 3, 4>;
    let y: <i32; 4> <: <+1:32, +2:32, +3:32, +4:32>;

    // Operations are performed component-wise.

    let r1 <: x + y;
    let r2 <: <not> x;

    // Elements can be accessed using the subscript operator.

    r1[0] <: 0;

    assert r1[0] == +0:32;
    assert r1[1] == +4:32;
    assert r1[2] == +6:32;
    assert r1[3] == +8:32;

    assert r2[0] == (<not> +1:32);
    assert r2[1] == (<not> +2:32);
    assert r2[2] == (<not> +3:32);
    assert r2[3] == (<not> +4:32);

    // All types can be used as element types.

    let a: <Data; 8>;

    return 0:32;
}

