// valid
// o: "A"

// In a while-loop, a break statement will cause the loop to exit immediately.

public main () : u32
{
    let count: size <: 0;

    while count < 4 do
    {
        count <: count + 1;

        let inner_count: size <: 0;

        while inner_count < 4 do
        {
            inner_count <: inner_count + 1;

            if inner_count == 2 then break;

            print(console, c"A");
        }

        if count == 1 then break;
    }

    return 0:32;
}
