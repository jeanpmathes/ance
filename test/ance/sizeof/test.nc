// valid

// The sizeof expressions allow to get the size of a type.

public main () : ui32
{
    // Two variants of the expression exist, one for types and one for the types returned by an expression.
    // Both variants return a value of type size.

    // The variant for types:

    let s1: size <: sizeof ui8;
    assert s1 == 1;

    // The variant for expressions:
    let x: i32;
    let s2: size <: sizeof(x);
    assert s2 == 4;

    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
