// valid

// For working with text, the character type 'char' can be used.
// A character contains one UTF-32 encoded code point.

public main () :  u32
{
    let c1: char <: 'a';
    let c2 <: 'b';

    // Literals can contain hexadecimal escape sequences.
    let c3 <: '\u{1F4A9}';

    let c4: char <: char( u32(c1));
    assert c4 == c1;

    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
