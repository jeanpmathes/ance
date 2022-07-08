// valid

// A program can define global variables. Global variables must be public or private.

// The value of global variables can be directly set when defining.
private g1: ui32 <: 100:32;

// If no initial value is given, the default value of the variable type is used.
private g2: ui32;

// Global variables can be declared as constant, in which case the initial value is not optional.
private const g3: ui32 := 100:32;

public main () : ui32
{
    // Local variables always have a value. When the initializer is missing, the type's default value is used.
    let l1: ui32;

    let l2: ui32 <: 100:32;
    let l3: ui32:= 100:32; // Final variable.

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
