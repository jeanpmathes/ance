// valid

// In function scopes, more anonymous scopes can be defined.

public main () : u32
{
    let x : u32 <: 0:32;

    {
        let x : u32 <: 1:32;
    }

    return x;
}

