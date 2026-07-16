// valid

// Array types can be created for most types and have a fixed length.

private arr1: [s32; 1];
private arr2: [s64; 2];
private arr3: [single; 4];
private arr4: [size; 16];
private arr5: [*u8; 32];
private arr6: [[s1; 2]; 64];
private arr7: [[[s1; 2]; 2]; 128];

// String arrays have special literals, that allow to declare array contents in a readable form.

private arr8: [u8; 3] <: 8"abc";

public main () : u32
{
    // Arrays provide subscript operators.

    let e: s32 <: arr1[0];
    arr1[0] <: e;

    // The return types of subscript operators are references to the element type.

    // For all array types, array definition expressions can be used to define a value.
    // The element type can be specified or inferred.

    let a1 <: [ 1:32, 2:32, 3:32, 4:32 ];
    let a2 <: [ u32 | 1, 2, 3, 4 ];

    assert a1[0] == 1:32;
    assert sizeof(a1) == sizeof u32 * 4:size;

    return 0:32;
}
