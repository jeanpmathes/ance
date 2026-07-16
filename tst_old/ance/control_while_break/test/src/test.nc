// valid
// o: "AAA"

// In a while-loop, a continue statement will skip the rest of the loop body and continue with the next iteration.

public main () : u32
{
    let count: size <: 0;

    while count < 4 do
    {
        count <: count + 1;

        // The continue can be nested in a block.
        {
            if count == 3 then continue;
        }

        print(console, c"A");
    }

    return 0:32;
}
