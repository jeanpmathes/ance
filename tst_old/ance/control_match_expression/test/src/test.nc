// valid
// o: "C"

// To select a value, match-expressions can be used.

public main () : u32
{
    let value: size <: 3;
    let c := c"C";

    let string: *u8 <: match value with
    {
        0:size => c"A",
        1:size => c"B",
        2:size | 3:size => c,
        4:size => c"D",
        default => c"E"
    };

    print(console, string);

    return 0:32;
}
