// valid
// o: "Hello, World!"

// Members of structs and other types can be accessed.

public struct MyString
{
    public str: *u8;
    public len: u32;
}

public main () : u32
{
    let s: MyString;
    s str <: c"Hello, World!";
    s len <: 13:32;

    print(console, s str);

    return 0:32;
}
