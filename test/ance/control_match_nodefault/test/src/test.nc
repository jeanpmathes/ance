// valid
// o: "true"

// Match-statements do not need a default case.

public main () : u32
{
    let value: bool <: true;

    match value with
    {
        false => print(console, c"false");
        true =>print(console, c"true");
    }

    return 0:32;
}
