// valid
// o: "A"

// The language allows to use return-statements for control flow.

private run ()
{
    print(console, c"A");

    if 12 == 12 then return;

    print(console, c"B");
}

public main () : u32
{
    run();
    return 0:32;
}
