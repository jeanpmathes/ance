// valid

// Constructors can be used for conversions, but fail when the conversion is not possible.

public main () : u32
{
    let i: size <: 12;
    let j: u32 <: u32(i);
    let k: uiptr <: j; // The constructor uiptr(j) would be unnecessary.
    let l: u64 <: u64(k);

    let b1: bool <: true;
    let b2: i1 <: i1(b1);
    let b3: bool <: bool(b2);

    return 0:32;
}

