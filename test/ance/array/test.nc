// valid

// Array types can be created for most types and have a fixed length.

private arr1: [i32; 1];
private arr2: [i64; 2];
private arr3: [single; 4];
private arr4: [size; 16];
private arr5: [*ui8; 32];
private arr6: [[i1; 2]; 64];
private arr7: [[[i1; 2]; 2]; 128];

// String arrays have special literals, that allow to declare array contents in a readable form.

private arr8: [ui8; 3] <: "abc";

public main () : ui32
{
    // Arrays provide indexers.

    let e: i32 <: arr1[0];
    arr1[0] <: e;

    // The return types of indexers are references to the element type.

    // For all array types, array definition expressions can be used to define a value.
    // The element type can be specified or inferred.

    let a1 <: [ 1:32, 2:32, 3:32, 4:32 ];
    let a2 <: [ ui32 | 1, 2, 3, 4 ];

    assert a1[0] == 1:32;
    assert sizeof(a1) == sizeof ui32 * 4:size;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);