// valid

// Unicode characters can be used in string and character literals as well as identifiers.
// Source file encoding is UTF-8.

public main () : u32
{
    let german_alphabet := "abcdefghijklmnopqrstuvwxyzäöüß";
    let ukranian_alphabet := "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
    let full_width_alphabet := "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ";
    let face_with_tears_of_joy := '😂';

    // Only letters, digits and underscore are allowed in identifiers.
    let ä := 1;
    let ї := 2;

    // A single emoji is also a valid identifier.

    let 😂 := 3;

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
