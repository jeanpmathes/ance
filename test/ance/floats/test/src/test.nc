// valid

// All floating point types and their literals.

private h1: half <: 0.0h;
private s1: single <: 0.0s;
private d1: double <: 0.0d;
private q1: quad <: 0.0q;

private h2: half <: .0h;
private s2: single <: .0s;
private d2: double <: .0d;
private q2: quad <: .0q;

private h3: half <: +0.0h;
private s3: single <: +0.0s;
private d3: double <: +0.0d;
private q3: quad <: +0.0q;

private h4: half <: -0.0h;
private s4: single <: -0.0s;
private d4: double <: -0.0d;
private q4: quad <: -0.0q;

public main () : u32
{
    return 0:32;
}

