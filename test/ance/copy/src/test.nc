// valid

// Using the copy assigner copies the value.

public struct Data
{
    public value: i32;
}

public main () : u32
{
    let v1: i32 <: +5:32;
    let c1: i32 <: v1;
    assert c1 == v1;

    let v2: [i32; 3];
    v2[0] <: +5:32;
    v2[1] <: +5:32;
    v2[2] <: +5:32;
    let c2: [i32; 3] <: v2;
    assert c2[0] == v2[0];
    assert c2[1] == v2[1];
    assert c2[2] == v2[2];

    let v3: Data;
    v3 value <: +5:32;
    let c3: Data <: v3;
    assert c3 value == v3 value;

    return 0:32;
}

