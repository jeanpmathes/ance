// invalid

// Extern functions cannot be overloaded with other extern functions.

public main () : ui32
{
    return 0:32;
}

public exit (exitcode : ui32)
{

}

extern overloaded ();
extern overloaded (x : ui32);