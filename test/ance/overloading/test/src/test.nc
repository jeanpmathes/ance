// valid
// o: "ABCDE"

// The language supports function overloading.

public main () : u32
{
    overloaded();
    overloaded(0:32);
    overloaded(0:64);
    overloaded(0:32, 0:32);

    // Overload resolution considers implicit conversions.
    overloaded(0.2h);

    return 0:32;
}

// The void return type can be omitted.

public overloaded ()
{
    print(console, c"A");
}

private overloaded (x: u32)
{
    print(console, c"B");
}

private overloaded (x: u64)
{
    print(console, c"C");
}

private overloaded (x: u32, y: u32)
{
    print(console, c"D");
}

private overloaded (x: single)
{
    print(console, c"E");
}
