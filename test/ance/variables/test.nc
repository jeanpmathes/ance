// valid

// A program can define global variables. Global variables must be public or private.
// Global variables are defined without order, they can be used above declaration.

// The value of global variables can be directly set when defining.
// All expressions are valid as initial values.
private g1: ui32 <: 100:32;
private g2: ui32 <: 100:32 + 200:32;
private g3: ui32 <: get_value() + 500:32;
private g4: ui32 <: if true then 200:32 else 100:32;

// The initial value is implicitly converted if necessary.
private g5: ui32 <: 100:16;

// If no initial value is given, the default value of the variable type is used.
private gt: ui32;

// Global variables can be declared as constant, in which case the initial value is not optional.
// The initial value of a constant must be available at compile time.
private const gc: ui32 := 100:32;

public main () : ui32
{
    // Local variables always have a value. When the initializer is missing, the type's default value is used.
    let l1: ui32;

    let l2: ui32 <: 100:32;
    let l3: ui32 := 100:32; // Final variable.

    assert g1 == 100:32;
    assert g2 == 300:32;
    assert g3 == 600:32;
    assert g4 == 200:32;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private get_value () : ui32
{
    return 100:32;
}

extern ExitProcess (uExitCode: ui32);
