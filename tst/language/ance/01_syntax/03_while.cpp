#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Conditional loops can be declared using the 'while' keyword.
    // The statement must be equivalent to a conversion in loop form.
    // As such, for the following 'while' construct...
    //
    // ```ance
    // while (CONDITION) do BODY
    // ```
    // ...the equivalent 'loop' construct is:
    //
    // ```ance
    // loop
    // {
    //     if not CONDITION then break;
    //     {
    //         BODY
    //     }
    // }
    // ```
    //
    // Therefore, both 'break' and 'continue' are allowed in 'while' loops.

    TEST_CASE("A 'while' statement repeats while its condition is true", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var count: Size := 0;

    while count < 4 do
    {
        log1str("A");
        count := count + 1;
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "A", {}}
                }
            }
        );
    }

    TEST_CASE("A 'break' exits the inner-most 'while' statement", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var outer_count: Size := 0;

    while outer_count < 4 do
    {
        outer_count := outer_count + 1;

        var inner_count: Size := 0;

        while inner_count < 4 do
        {
            inner_count := inner_count + 1;

            if inner_count == 2 then break;

            log1str("A");
        }

        log1s(outer_count);
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "1", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "2", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "3", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "4", {}}
                }
            }
        );
    }

    TEST_CASE("A 'continue' begins the next 'while' iteration", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var count: Size := 0;

    while count < 4 do
    {
        count := count + 1;

        if count == 3 then continue;

        log1str("A");
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "A", {}}
                }
            }
        );
    }
}
