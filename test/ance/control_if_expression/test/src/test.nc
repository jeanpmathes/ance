// valid
// o: "TF"

// Instead of using if-statements, if-expression can be used too.

public main () : u32
{
    let b : bool <: true;

    // Only the expression that will actually provide the value is evaluated.

    b <: if true then get_true() else get_false();
    b <: if false then get_true() else get_false();

    // The if-expression can be used to formulate implications.
    // This works because the for the boolean type, the else-branch is set to true if not provided.

    assert (if false then false) == true;
    assert (if false then true) == true;
    assert (if true then false) == false;
    assert (if true then true) == true;

    return 0:32;
}

private get_true () : bool
{
    print(console, c"T");
    return true;
}

private get_false () : bool
{
    print(console, c"F");
    return false;
}
