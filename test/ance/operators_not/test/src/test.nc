// valid

// For logical operations, the not operator can be used.

public main () : u32
{
    assert not false;
    assert not not true;

    // The not operator can be applied directly to the operators 'and' and 'or'.
    // This will negate the result of the operation. It is equivalent to negating the parenthesized expression.

    let a1 <: not (true or false);
    let b1 <: true not or false;
    assert a1 == b1;

    let a2 <: not (true and false);
    let b2 <: true not and false;
    assert a2 == b2;

    return 0:32;
}

