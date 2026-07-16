// invalid

// Every overload must have a unique signature.

public main () : u32
{
    return 0:32;
}


extern overloaded (x: u32);
extern overloaded (y: u32);
