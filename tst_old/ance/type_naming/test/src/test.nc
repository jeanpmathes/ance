// invalid

// In the global scope and other unordered scopes, every name can be used at most once.

public nameA () {}
public nameA: s32;

public nameB: s32;
public define nameB alias s32;

public struct nameC {}
public nameC () {}

public main () : u32
{
    return 0:32;
}

