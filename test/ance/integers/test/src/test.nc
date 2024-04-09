// valid

// Different fixed-width integer types and their literals.

private x1: s1 <: +0:1;
private x2: s2 <: +0:2;
private x3: s3 <: +0:3;
private x4: s4 <: +0:4;
private x5: s5 <: +0:5;
private x6: s6 <: +0:6;
private x7: s7 <: +0:7;
private x8: s8 <: +0:8;
private x9: s9 <: +0:9;
private x10: s10 <: +0:10;
private x11: s11 <: +0:11;
private x12: s12 <: +0:12;
private x13: s13 <: +0:13;
private x14: s14 <: +0:14;
private x15: s15 <: +0:15;
private x16: s16 <: +0:16;
private x17: s17 <: +0:17;
private x18: s18 <: +0:18;
private x19: s19 <: +0:19;
private x20: s20 <: +0:20;
private x21: s21 <: +0:21;
private x22: s22 <: +0:22;
private x23: s23 <: +0:23;
private x24: s24 <: +0:24;
private x25: s25 <: +0:25;

private x26: s32 <: +0:32;
private x27: s64 <: +0:64;
private x28: s128 <: +0:128;
private x29: s256 <: +0:256;
private x30: s512 <: +0:512;
private x31: s1024 <: +0:1024;
private x32: s2048 <: +0:2048;

private x33: u1 <: 0:1;
private x34: u2 <: 0:2;
private x35: u3 <: 0:3;
private x36: u4 <: 0:4;
private x37: u5 <: 0:5;
private x38: u6 <: 0:6;
private x39: u7 <: 0:7;
private x40: u8 <: 0:8;
private x41: u9 <: 0:9;
private x42: u10 <: 0:10;
private x43: u11 <: 0:11;
private x44: u12 <: 0:12;
private x45: u13 <: 0:13;
private x46: u14 <: 0:14;
private x47: u15 <: 0:15;
private x48: u16 <: 0:16;
private x49: u17 <: 0:17;
private x50: u18 <: 0:18;
private x51: u19 <: 0:19;
private x52: u20 <: 0:20;
private x53: u21 <: 0:21;
private x54: u22 <: 0:22;
private x55: u23 <: 0:23;
private x56: u24 <: 0:24;
private x57: u25 <: 0:25;

private x58: u32 <: 0:32;
private x59: u64 <: 0:64;
private x60: u128 <: 0:128;
private x61: u256 <: 0:256;
private x62: u512 <: 0:512;
private x63: u1024 <: 0:1024;
private x64: u2048 <: 0:2048;

public main () : u32
{
    // Integer literals without type suffixes use the smallest possible fixed-width integer type.
    let x65: s32 <: 5;
    let x66: s32 <: -5;
    let x67: u32 <: 5;

    return 0:32;
}

