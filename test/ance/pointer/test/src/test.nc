// valid

// Pointer types are available for most types.

public main () : u32
{
    let a1: *u32;
    let a2: *size;
    let a3: ****single;

    // The default value of pointers is null.
    let a4: *u32;
    let a5: *u32 <: null;
    assert a4 == a5;

    // The null literal has the special nullptr type.
    let a6: nullptr <: null;

    // Pointers can be converted to the opaque pointer type 'ptr' and to the 'uiptr' type.
    let a7 <: a1 as ptr;
    let a8 <: a1 as uiptr;

    // Values of both of these types can be converted back to pointers and to each other.
    let a9 <: a7 as *u32;
    let a10 <: a8 as *u32;
    let a11 <: a8 as ptr;
    let a12 <: a7 as uiptr;

    // Pointers can not be directly converted to each other.
    let a13 <: a1 as ptr as *i32;
    let a14 <: a13 as ptr as *u32;

    // Buffer-pointers work just like pointers in respect to the above.
    let a15 <: a1 as ptr as []u32;
    let a16 <: a15 as ptr as *u32;

    return 0:32;
}
