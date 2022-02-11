// valid

// Special number literals. The hexadecimal, octal, and binary literals are only valid with type suffixes.

private hex1: ui8 <: 0xFF:8;
private hex2: ui16 <: 0xFF:16;
private hex3: ui32 <: 0xFF:32;
private hex4: ui64 <: 0xFF:64;

private oct1: ui8 <: 0o377:8;
private oct2: ui16 <: 0o377:16;
private oct3: ui32 <: 0o377:32;
private oct4: ui64 <: 0o377:64;

private bin1: ui8 <: 0b11111111:8;
private bin2: ui16 <: 0b11111111:16;
private bin3: ui32 <: 0b11111111:32;
private bin4: ui64 <: 0b11111111:64;

// Byte literals.

private byte1: ui8 <: 'A';
private byte2: ui8 <: '\0';
private byte3: ui8 <: '\n';

public main () : ui32
{
    return 0:32;
}

public exit (exitcode: ui32)
{
     ExitProcess(exitcode);
}

extern ExitProcess (uExitCode: ui32);
