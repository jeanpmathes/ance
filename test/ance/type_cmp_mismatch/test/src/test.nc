// invalid

// All syntactic structures expect specific types to be provided.

private struct DefinedStruct { }
private variable: i32 := DefinedStruct; // This requires a value, not a type.

private defined_variable: i32 := 0;
private defined_function ()
{
    let x := new dynamic defined_variable; // This requires a type, not a value.
    let y := defined_variable(); // This requires a function group or a type, not a value.
}

public main () : u32
{
    return 0:32;
}

