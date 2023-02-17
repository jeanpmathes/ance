// invalid

// Extern functions cannot be overloaded with other extern functions.
// The reason is that extern functions are not mangled.

public main () : u32
{
    return 0:32;
}


extern overloaded ();
extern overloaded (x: u32) {}