// valid
// o: "Y"

// Variables can be redefined in the same scope they are defined.

public main () : u32
{
    let x : size <: 1;
    x <: 2;

    let x : *u8 <: c"X";
    x <: c"Y";

    print(console, x);

    // Previously defined variables can be used in their redefinition.
    let x <: 12;
    let x <: x + 1;
    assert x == 13;

    return 0:32;
}
