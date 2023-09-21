// invalid

// A variable can only be erased in the same scope it was declared in.

public main () : u32
{
    let x: size <: 15;

    {
        erase x; // Will not compile.
    }

    return 0:32;
}

