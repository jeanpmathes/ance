// valid

// Special number literals. The hexadecimal, octal, and binary literals are only valid with type suffixes.

private hex1:  u8 <: 0xFF:8;
private hex2:  u16 <: 0xFF:16;
private hex3:  u32 <: 0xFF:32;
private hex4:  u64 <: 0xFF:64;

private oct1:  u8 <: 0o377:8;
private oct2:  u16 <: 0o377:16;
private oct3:  u32 <: 0o377:32;
private oct4:  u64 <: 0o377:64;

private bin1:  u8 <: 0b11111111:8;
private bin2:  u16 <: 0b11111111:16;
private bin3:  u32 <: 0b11111111:32;
private bin4:  u64 <: 0b11111111:64;

// Byte literals can either by a single character or an escape sequence.

private byte1:  u8 <: 8'A';
private byte2:  u8 <: 8'\0';
private byte3:  u8 <: 8'\n';

// Unsigned integer pointer literals are always hexadecimals.

private p1: uiptr <: 0x1234:uiptr;
private p2: uiptr <: 0x0000:uiptr;

public main () :  u32
{
    return 0:32;
}

public exit (exitcode:  u32)
{
    ExitProcess(exitcode);
}

extern ExitProcess (uExitCode:  u32);
