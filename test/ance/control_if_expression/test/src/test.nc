// valid
// o: "TF"

// Instead of using if-statements, if-expression can be used too.

public main () : u32
{
    let b : bool <: true;

    // Only the expression that will actually provide the value is evaluated.

    b <: if true then get_true() else get_false();
    b <: if false then get_true() else get_false();

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
