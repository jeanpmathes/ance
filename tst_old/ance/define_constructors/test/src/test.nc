// valid

// Alias definitions allow using the constructors of the aliased type.

private define Alias alias u8;

private fn (a: *Alias) {}

public main () : u32
{
    let a: s8;
    let b: Alias := Alias(a);

    return 0:32;
}
