// invalid

// A hidden variable cannot be unhidden by erasing the hiding variable.

public main () : u32
{
    let x: size <: 15;

    {
        // The outer x is hidden in this scope.

        let x: single <: 0.0s;
        erase x;

        let z: size <: x; // Will not compile.
    }

    let z: size <: x;

    return 0:32;
}

