// valid

// Instead of a void type, the unit type is used.

private struct X
{
    private x: ();
    private y: ();
    private z: ();
}

public unit: ();

private foo () : () // This does not have to be specified explicitly, see below.
{
    let x: () <: (); // The unit literal can be used to get a unit type value.

    // The unit type can be used everywhere any other type can be used.
    let y: [(); 3];
    let z: *();

    assert sizeof () == 0:size;
    assert sizeof X == 0:size;

    let p: *() <: null;
    let q: () <: p.;
    p. <: ();
}

private bar ()
{

}

public main () : u32
{
    return 0:32;
}

