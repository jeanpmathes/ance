// valid

// A program can define global variables. Global variables must be public or private.
// Global variables are defined without order, they can be used above declaration.

// The value of global variables can be directly set when defining.
// All expressions are valid as initial values.
private g1: u32 <: 100:32;
private g2: u32 <: 100:32 + 200:32;
private g3: u32 <: get_value() + 500:32;
private g4: u32 <: if true then 200:32 else 100:32;

// The initial value is implicitly converted if necessary.
private g5: u32 <: 100:16;

// The type can be inferred like the initial value.
private g6 <: 100:32;

// If no initial value is given, the default value of the variable type is used.
private gt: u32;

// Global variables can be declared as compile-time, in which case the initial value is not optional.
// The initial value of such a variable / constant must be defined on declaration.
private cmp gc: u32 := 100:32;

public main () : u32
{
    // Local variables always have a value. When the initializer is missing, the type's default value is used.
    let l1: u32;

    let l2: u32 <: 100:32;
    let l3: u32 := 100:32; // Final variable.

    assert g1 == 100:32;
    assert g2 == 300:32;
    assert g3 == 600:32;
    assert g4 == 200:32;

    return 0:32;
}

private get_value () : u32
{
    return 100:32;
}
