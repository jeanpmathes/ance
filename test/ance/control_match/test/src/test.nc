// valid
// o: "CCC"

// The language allows to use match-statements for control flow. These are similar to switch-cases.

public main () : u32
{
    // Match statements are supported for all integer types.
    // These are fixed-width integers, size-types and integer pointers.
    // Additionally, boolean types are supported.

    let value: size <: 3;

    match value with
    {
        0:size => print(console, c"A"); // No break is required, because no fallthrough is possible.
        1:size => print(console, c"B");
        2:size | 3:size => print(console, c"C");
        4:size =>
        {
            print(console, c"D");
        }
        default => print(console, c"E");
    }

    let value: i32 <: 3;

    match value with
    {
        +0:32 => print(console, c"A");
        +1:32 => print(console, c"B");
        +2:32 | +3:32 => print(console, c"C");
        +4:32 =>
        {
            print(console, c"D");
        }
        default => print(console, c"E");
    }

    let value: uiptr <: 0x3:uiptr;

    match value with
    {
        0x0:uiptr => print(console, c"A");
        0x1:uiptr => print(console, c"B");
        0x2:uiptr | 0x3:uiptr => print(console, c"C");
        0x4:uiptr =>
        {
            print(console, c"D");
        }
        default => print(console, c"E");
    }

    return 0:32;
}
