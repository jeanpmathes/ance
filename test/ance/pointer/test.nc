// valid

// Pointer types are available for most types.

public main () :  u32
{
    let a1: * u32;
    let a2: *size;
    let a3: ****single;

    // The default value of pointers is null.
    let a4: * u32;
    let a5: * u32 <: null;
    assert a4 == a5;

    // The null literal has the special nullptr type.
    let a6: nullptr <: null;

    // Pointers can be converted to the opaque pointer type 'ptr' and to the 'uiptr' type.
    let a7 <: ptr(a1);
    let a8 <: uiptr(a1);

    // Values of both of these types can be converted back to pointers and to each other.
    let a9 <: * u32(a7);
    let a10 <: * u32(a8);
    let a11 <: ptr(a8);
    let a12 <: uiptr(a7);

    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
