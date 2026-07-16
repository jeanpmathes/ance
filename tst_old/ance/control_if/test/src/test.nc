// valid
// o: "AD"

// The language allows to use if-else-statements for control flow.

public main () : u32
{
    if 12 == 12 then print(console, c"A");

    if 12 == 14 then
    {
        print(console, c"B");
    }
    else if 13 == 14 then
    {
        print(console, c"C");
    }
    else
    {
        print(console, c"D");
    }

    return 0:32;
}
