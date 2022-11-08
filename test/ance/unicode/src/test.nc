// valid

// Unicode characters can be used in string and character literals.
// Source file encoding is UTF-8.

public main () : u32
{
    let german_alphabet := "abcdefghijklmnopqrstuvwxyzäöüß";
    let russian_alphabet := "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    let full_width_alphabet := "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ";
    let face_with_tears_of_joy := '😂';

    return 0:32;
}

public exit (exitcode: u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: u32);
