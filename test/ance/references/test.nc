// valid

// Both references and pointers can be used.

public main () : ui32
{
    let num: size <: 100;

    // Get the address of a variable using addressof.
    let num_ptr: *size <: addressof num;

    // References can be bound directly to a variable or to a pointer.
    let num_r1: &size ref num;
    let num_r2: &size ref to num_ptr;
    let num_r3: &size ref num_r1; // References can also be bound to variables over other references.

    // Passing references to functions requires binding.
    modify_num(ref num);

    let num2: size;

    // Using references behaves just like using the referenced variable. The following statements both do the same.
    num2 <: num;
    num2 <: num_r1;

    return 0:32;
}

private modify_num (num: &size)
{
    // Assignment to references changes the value of the referenced variable.
    num <: 0;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
