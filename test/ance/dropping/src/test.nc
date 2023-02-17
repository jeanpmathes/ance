// valid

// Variables can be dropped in the scope that they are declared in.

public main () : u32
{
    let x: size <: 15;
    let y: size <: x;

    drop x;

    // x cannot be used here, because it has been dropped.

    return 0:32;
}

