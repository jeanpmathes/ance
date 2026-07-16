// invalid

// Not all statements and expressions are valid in a cmp context.

private cmp foo ()
{
    main(); // Cannot call a non-cmp function from a cmp function.
}

public main () : u32
{
    return 0:32;
}
