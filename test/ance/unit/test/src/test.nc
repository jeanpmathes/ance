// valid

// Instead of a void type, the unit type is used.

private struct X
{
    public x: ();
    public y: ();
    public z: Y;
}

private struct Y { }

public unit: ();

public foo () : () // This does not have to be specified explicitly, see below.
{
    let x: () <: (); // The unit literal can be used to get a unit type value.

    // The unit type can be used everywhere any other type can be used.
    let y: [(); 3];
    let z: *();

    x <: y[1];

    assert sizeof () == 0:size;
    assert sizeof X == 0:size;
    assert sizeof Y == 0:size;

    let p: *() <: addressof x;
    let q: () <: p.;
    p. <: ();

    let p2: *() <: p + 1:size;
    let q2: () <: p2.;
    p2. <: ();

    let a: X;
    a x <: ();
    a y <: ();

    let a := new automatic ();
    delete a;

    let a := new[3] automatic ();
    delete[] a;

    bar(());
}

private bar (u: ())
{

}

public main () : u32
{
    foo();
    return 0:32;
}

