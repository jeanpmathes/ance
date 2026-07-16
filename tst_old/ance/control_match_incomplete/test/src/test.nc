// invalid

// Match-statements must complete cover all possible cases.

public main () : u32
{
    let value: size <: 3;

    match value with
    {
        0:size => print(console, c"A"); // Only one case covered.
    }

    return 0:32;
}
