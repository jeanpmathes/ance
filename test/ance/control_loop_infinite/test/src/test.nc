// invalid

// Code after a loop is unreachable, if there is no break statement.

public main () : u32
{
    loop {}

    return 0:32; // This is unreachable, causing a warning. As warnings are treated as errors, this is invalid.
}

