// invalid

// A variable that has been erased cannot be used.

public main () : u32
{
    let x: size <: 15;
    let y: size <: x;

    erase x;

    let z: size <: x; // Will not compile.

    return 0:32;
}

