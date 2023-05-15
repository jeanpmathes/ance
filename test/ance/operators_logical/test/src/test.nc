// valid
// o: "TTFFFT"

// For logical operations, the operators 'and' and 'or' can be used.
// Both operators are short-circuiting.

public main () : u32
{
    assert true and true;
    assert true or false;
    assert false or true;

    // In these cases both expressions have to be evaluated:

    let b1 : bool <: get_true() and get_true();
    let b2 : bool <: get_false() or get_false();

    // In these cases only the first expression has to be evaluated:

    let b3 : bool <: get_false() and get_false();
    let b4 : bool <: get_true() or get_true();

    assert b1;
    assert not b2;
    assert not b3;
    assert b4;

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
