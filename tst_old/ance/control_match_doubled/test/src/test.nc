// invalid

// Every case of a match-statement must be unique.

public main () : u32
{
    let value: size <: 3;

    match value with
    {
        0:size => print(console, c"A");
        0:size => print(console, c"B"); // Case 0 is already defined.
        default => print(console, c"C");
    }

    return 0:32;
}
