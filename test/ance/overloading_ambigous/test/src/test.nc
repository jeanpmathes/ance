// invalid

// As overload resolution takes implicit conversions into account, ambiguous function calls are possible.
// An ambiguous function call is invalid code.

public main () : u32
{
    ambiguous(0:8);

    return 0:32;
}

private ambiguous (x: s64) {}
private ambiguous (x: s128) {}
