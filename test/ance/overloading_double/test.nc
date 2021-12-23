// invalid

// Every overload must have a unique signature.

public main () : ui32
{
    return 0:32;
}

public exit (exitcode : ui32)
{

}

extern overloaded (x : ui32);
extern overloaded (y : ui32);
