// valid
// o: "ABC"

// There are multiple types of string literals.

// Byte character array literals create an array that contains the specified characters.
// Text is encoded using UTF-8.

private str1: [u8; 0] <: 8"";
private str2: [u8; 1] <: 8"\u{0}"; // Unicode code point escapes are supported in string literals.
private str3: [u8; 2] <: 8"AB";
private str4: [u8; 3] <: 8"ABC";

// C-style string literals contain a pointer to a null-terminated char sequence.
// Text is encoded using UTF-8.

private str5: *u8 <: c"";
private str6: *u8 <: c"\u{0}";
private str7: *u8 <: c"AB";
private str8: *u8 <: c"ABC";

// Char character array literals create an array that contains the specified characters.
// Text is encoded using UTF-32.

private str9: [char; 0] <: "";
private str10: [char; 1] <: "\u{0}";
private str11: [char; 2] <: "AB";
private str12: [char; 3] <: "ABC";

public main () : u32
{
    print(console, str8);

    return 0:32;
}
