// valid

// Casts can be used to convert between types.
// Casts will always result in a valid value of the target type, but may cause loss of information.

public main () : u32
{
    let i: size <: 12;
    let j: u32 <: i as u32;
    let k: uiptr <: j; // The cast from u32 to uiptr is covered by implicit conversions and thus unnecessary.
    let l: u64 <: k as u64;

    let f1: single <: 12.0s;
    let f2: double <: f1;
    let f3: single <: f2 as single;

    let b1: bool <: true;
    let b2: s1 <: s1(b1); // Booleans cannot be casted, because constructors allow safe conversion in all cases.
    let b3: bool <: bool(b2);

    return 0:32;
}

