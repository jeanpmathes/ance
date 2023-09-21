// valid

// Variables can be erased in the scope that they are declared in.

public main () : u32
{
    let x: size <: 15;
    let y: size <: x;

    erase x;

    // x cannot be used here, because it has been erased.

    return 0:32;
}

