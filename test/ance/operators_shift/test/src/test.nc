// valid

// Bitshift operations are available for all integer types.

public main () : u32
{
    let x: s32 <: 0x00000001:16;
    let y: u32 <: 0x00000001:16;

    // The shift count must be an unsigned integer.

    let r1: s32 <: x <sl> 3;
    let r2: s32 <: x <sr> 3; // Arithmetic shift right, because x is signed.
    let r3: u32 <: y <sl> 4;
    let r4: u32 <: y <sr> 4; // Logical shift right, because y is unsigned.

    return 0:32;
}

