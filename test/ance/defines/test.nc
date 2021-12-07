// valid

// New types can be defined using existing types.

// Type clones are a new type that behaves like the original type.
define clone1 as i64;
define clone2 as clone1;

// Type aliases are just a placeholder for an actual type.
define alias1 alias size;
define alias2 alias alias1;

// The order in the source file is not important.
define clone3 as clone4;
define clone4 as clone1;

public main () : ui32
{
    // Type aliases can be used as if they were the actual type.
    let a : size <: 42;
    let b : alias1 <: 42;
    let c : alias2 <: 42;

    a <: b;
    b <: c;
    c <: a;

    return 0:32;
}

public exit (exitcode : ui32)
{

}
