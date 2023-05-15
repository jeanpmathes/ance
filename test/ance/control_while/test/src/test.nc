// valid
// o: "AAAA"

// The language allows to use while-statements for control flow.

public main () : u32
{
    let count: size <: 0;

    while count < 4 do
    {
        print(console, c"A");
        count <: count + 1;
    }

    return 0:32;
}
