// valid

// New types can be defined using existing types.

// Type aliases are just a placeholder for an actual type.
public define Alias1 alias size;
public define Alias2 alias Alias1;

// The order in the source file is not important.
public define Alias3 alias Alias4;
public define Alias4 alias Alias1;

// Reference types can be aliased too, but double-refs still aren't allowed.
public define Ref alias &size;

public main () : u32
{
    // Type aliases can be used alias if they were the actual type.
    let a: size <: 42;
    let b: Alias1 <: 42;
    let c: Alias2 <: 42;

    a <: b;
    b <: c;
    c <: a;

    let ra: &size ref a;
    let rb: Ref ref b;

    ra <: a;
    rb <: b;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
