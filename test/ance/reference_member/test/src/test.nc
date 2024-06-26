// valid

// References permit accessing a member just as if the referenced variable would be used.

public struct Data
{
    public x: s64;
    public y: s64;
}

public main () : u32
{
    let d: Data;
    d x <: 1;

    let d_ref: &Data ref d;
    d_ref x <: 2;

    assert d x == +2:64;

    return 0:32;
}

