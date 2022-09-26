// valid

// Testing the results of many of the mathematical operators.

public main () : ui32
{
    test_fw_integer_math();
    test_float_math();
    test_size_math();
    test_uiptr_math();

    return 0:32;
}

private test_fw_integer_math ()
{
    let x1: i32 <: -1:32;
    let x2: i32 <: +1:32;

    assert x1 == -1:32;
    assert x2 == +1:32;

    assert x2 > x1;
    assert x1 < x2;

    assert x1 + x2 == +0:32;
    assert x1 - x2 == -2:32;
    assert x1 * x2 == -1:32;
    assert x1 / x2 == -1:32;
    assert x1 % x2 == +0:32;

    let x3: ui32 <: 1:32;
    let x4: ui32 <: 2:32;

    assert x3 + x4 == 3:32;
    assert x4 - x3 == 1:32;

    assert x3 < x4;
    assert x3 <= x4;
}

private test_float_math ()
{
    let x1: half <: -1.0h + 1.0h;
    let x2: single <: +1.0s - 1.0s;
    let x3: double <: +1.0d - 1.0d;
    let x4: quad <: +1.0q - 1.0q;

    assert x1 == 0.0h;
    assert x2 == 0.0s;
    assert x3 == 0.0d;
    assert x4 == 0.0q;

    assert 1.0s >= 1.0s;
    assert 1.0d <= 1.0d;
}

private test_size_math ()
{
    let x1: size <: 1;
    let x2: size <: 2;

    assert x1 - x2 > 0;

    assert 2:size + 3:size * 2:size == 8:size;
    assert 2:size * 3:size + 2:size == 8:size;
    assert 2:size * (3:size + 2:size) != 8:size;
}

private test_uiptr_math ()
{
    let x1: uiptr <: 0x00000001:uiptr;
    let x2: uiptr <: 0x00000002:uiptr;

    assert x1 + x2 == 0x00000003:uiptr;
}

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
