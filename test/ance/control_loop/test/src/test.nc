// valid

// Loop statements repeat the contained statement forever, except when a break or similar statement is encountered.

public main () : u32
{
    loop break;

    loop
    {
        break;
    }

    return 0:32;
}

