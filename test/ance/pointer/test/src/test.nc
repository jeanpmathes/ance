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
    let a7 <: ptr(a1);
    let a8 <: uiptr(a1);

    // Values of both of these types can be converted back to pointers and to each other.
    let a9 <: *u32(a7);
    let a10 <: *u32(a8);
    let a11 <: ptr(a8);
    let a12 <: uiptr(a7);

    // Pointers can also directly be converted to each other.
    let a13 <: *i32(a1);
    let a14 <: *u32(a13);

    // Buffer-pointers work just like pointers in respect to the above.
    let a15 <: []u32(a1);
    let a16 <: *u32(a15);

    return 0:32;
}
