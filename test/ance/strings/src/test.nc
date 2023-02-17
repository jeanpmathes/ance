// valid
// o: "ABC\0"

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

private std_out: Handle;

public define Handle alias ptr;

public main () : u32
{
    std_out <: GetStdHandle(4294967285:32);

    write(str8, 4:32);

    return 0:32;
}

private write (str: *u8, len: u32)
{
    let written: *u32 <: new automatic u32;
    WriteFile(std_out, str, len, written, null);
}

extern WriteFile (hFile: Handle, lpBuffer: *u8, nNumberOfBytesToWrite: u32, lpNumberOfBytesWritten: *u32, lpOverlapped: ptr);
extern GetStdHandle (nStdHandle: u32) : Handle;
