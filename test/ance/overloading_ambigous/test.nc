// invalid

// As overload resolution takes implicit conversions into account, ambiguous function calls are possible.
// An ambiguous function call is invalid code.

public main () : ui32
{
    ambiguous(0:8);

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

private ambiguous (x: i64) {}
private ambiguous (x: i128) {}

extern ExitProcess (uExitCode: ui32);
