// valid

// Vector types can be used to perform operations on a vector of values.

public struct Data
{
    public x: uiptr;
    public y: [*i8; 3];
    public z: single;
}

public main () : ui32
{
    // A vector type consists of element type and element count.
    // A vector literal is a list of elements and optionally the vector type.

    let x <: <i32 | 1, 2, 3, 4>;
    let y: <i32; 4> <: <1:32, 2:32, 3:32, 4:32>;

    // Operations are performed component-wise.

    let z = x + y;

    // Elements can be accessed using the index operator.

    z[0] <: 0;

    assert z[0] == 0;
    assert z[1] == 4;
    assert z[2] == 6;
    assert z[3] == 8;

    // All types can be used as element types.

    let a: <Data; 8>;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
