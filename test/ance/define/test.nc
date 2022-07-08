// valid

// New types can be defined using existing types.

// Type clones are a new type that behaves like the original type.
public define Clone1 as i64;
public define Clone2 as Clone1;

// Type aliases are just a placeholder for an actual type.
public define Alias1 alias size;
public define Alias2 alias Alias1;

// The order in the source file is not important.
public define Clone3 as Clone4;
public define Clone4 as Clone1;

// Reference types can be aliased too, but double-refs still aren't allowed.
public define Ref alias &size;

public main () : ui32
{
    // Type aliases can be used as if they were the actual type.
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

public exit (exitcode: ui32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
