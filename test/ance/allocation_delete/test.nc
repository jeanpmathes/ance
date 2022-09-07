// invalid

// Different pointer types require different deletion operations.

public main () : ui32
{
    let ptr_to_single <: new dynamic i64;
    delete[] ptr_to_single; // Error, delete[] requires a pointer to buffer.

    let ptr_to_buffer <: new[12] dynamic i64;
    delete ptr_to_buffer; // Error, delete requires a pointer to single.

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
