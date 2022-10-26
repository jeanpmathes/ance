// valid

// Each struct member can be given a value it is initialized to.

private struct Values
{
    public a: i32 <: +15:32;
    public b: *ui8 <: c"A";
    public c: bool;
}

public main () : ui32
{
    let v: Values; // Struct members are initialized here.

    assert v a == +15:32;
    assert v b[0] == 8'A';
    assert not v c;

    // Allocating a value will also initialize it.
    let v_ptr: *Values <: new dynamic Values;
    assert v_ptr.a == +15:32;
    delete v_ptr;

    // Allocating a buffer will initialize all of its elements.
    let v_buffer: []Values <: new[3] dynamic Values;
    assert v_buffer[0] a == +15:32;
    assert v_buffer[1] a == +15:32;
    assert v_buffer[2] a == +15:32;
    delete[] v_buffer;

    // Array members are also initialized.
    let v_array: [Values; 3];
    assert v_array[0] a == +15:32;
    assert v_array[1] a == +15:32;
    assert v_array[2] a == +15:32;

    return 0:32;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
