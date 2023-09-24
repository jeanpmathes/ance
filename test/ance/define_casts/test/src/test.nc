// valid

// Alias definitions allow using the casts of the aliased type.

private define Alias alias *u8;

private fn (a: *Alias) {}

public main () : u32
{
    let a: *i8;
    let b: Alias := a as Alias;

    let c: **i8;
    let d: *Alias := c as *Alias;

    let f: []*i8;
    let g: []Alias := f as []Alias;

    return 0:32;
}
