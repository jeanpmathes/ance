// invalid

private foo () : size
{
    let x: size := x_var[0]; // Cannot convert from double to size here.
    return x;
}

private main() : u32 { return 0; }

private x_var := [12.0d];
