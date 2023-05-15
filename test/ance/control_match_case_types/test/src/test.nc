// invalid

// The conditions of the match cases must be all of the same type, have the same type as the matched value.

public main () : u32
{
    let value: size <: 3;

    match value with
    {
        0:size => print(console, c"A");
        1 => print(console, c"B"); // Literal 1 is not a 'size' type value.
        default => print(console, c"C");
    }

    return 0:32;
}
