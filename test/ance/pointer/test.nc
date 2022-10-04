// valid

// Pointer types are available for most types.

public main () : ui32
{
    let a1: *ui32;
    let a2: *size;
    let a3: ****single;

    // The default value of pointers is null.
    let a4: *ui32;
    let a5: *ui32 <: null;
    assert a4 == a5;

    // The null literal has the special nullptr type.
    let a6: nullptr <: null;

    // Pointers can be converted to the opaque pointer type 'ptr' and to the 'uiptr' type.
    let a7 <: ptr(a1);
    let a8 <: uiptr(a1);

    // Values of both of these types can be converted back to pointers and to each other.
    let a9 <: *ui32(a7);
    let a10 <: *ui32(a8);
    let a11 <: ptr(a8);
    let a12 <: uiptr(a7);

    // The 'uiptr' type is used for pointer arithmetic.
    let p1 <: 0x100:uiptr;
    let p2 <: 0x200:uiptr;
    let p3 <: p1 + 0x100:uiptr;
    assert p3 == p2;
    assert ptr(p3) == ptr(p2);

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
