// valid

// Alias definitions allow using the casts of the aliased type.

private define Alias alias *u8;

private fn (a: *Alias) {}

public main () : u32
{
    let a: *s8;
    let b: Alias := a as ptr as Alias;

    let c: **s8;
    let d: *Alias := c as ptr as *Alias;

    let f: []*s8;
    let g: []Alias := f as ptr as []Alias;

    return 0:32;
}
