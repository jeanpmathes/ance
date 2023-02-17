// invalid

// Structs cannot hold values of their own type.

public struct Data
{
    private d: Data;
}

public main () : u32
{
    return 0:32;
}

