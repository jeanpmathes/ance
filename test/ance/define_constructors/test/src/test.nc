// valid

// Alias definitions allow using the constructors of the aliased type.

private define Alias alias *u8;

private fn (a: *Alias) {}

public main () : u32
{
    let a: *i8;
    let b: Alias := Alias(a);

    let c: **i8;
    let d: *Alias := *Alias(c);

    let f: []*i8;
    let g: []Alias := []Alias(f);

    return 0:32;
}
