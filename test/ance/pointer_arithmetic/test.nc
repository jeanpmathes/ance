// valid

// Pointers can be used for some arithmetic operations.

public main () :  u32
{
    // The 'uiptr' type is used for numerical operations on pointers.
    let v1 <: 0x100:uiptr;
    let v2 <: 0x200:uiptr;
    let v3 <: v1 + 0x100:uiptr;
    assert v3 == v2;
    assert ptr(v3) == ptr(v2);

    let v: i32 := 500;

    let p1: *i32 <: addressof v;
    let offset: diff <: 15;

    // Adding a diff value to a pointer will offset the pointer.
    let p2 <: p1 + offset;
    assert uiptr(p2) == uiptr(p1) + uiptr(offset * sizeof i32);

    // Subtracting two pointers will return the difference between them.
    let difference <: p2 - p1;
    assert difference == offset;

    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
