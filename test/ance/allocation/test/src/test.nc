// valid

// Memory allocation mechanisms.

public main () : u32
{
    // Dynamic memory is allocated using new.
    let ptr_to_int: *i32 <: new dynamic i32;

    // Dynamically allocated memory must be freed using delete.
    delete ptr_to_int;

    // Allocating buffers returns a buffer-pointer.
    let str: []u8 <: new[3] dynamic u8;

    str[0] <: 8'A';
    str[1] <: 8'B';
    str[2] <: 8'C';

    // Buffers must be freed using delete[].
    delete[] str;

    return 0:32;
}
