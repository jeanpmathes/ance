#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language allows checking of conditions using 'if' and 'else' statements.
    // This statement evaluates an expression that provides a value of type 'Bool'.
    // If the value is 'true', the first branch is executed, otherwise, the second branch is executed.
    // The second branch can be omitted, in which case none of the branches is evaluated on 'false'.
    //
    // 'if' can also be used as an expression, which returns the value of the taken branch.
    // Unlike in an 'if' statement, the 'else' branch is mandatory for the expression, as
    // an expression must always return a value. The expression form is expanded to a
    // block containing an 'if' statement. As such, for the following 'if' expression...
    //
    // ```ance
    // if CONDITION then THEN else ELSE
    // ```
    // ...the equivalent expansion is:
    //
    // ```ance
    // {
    //     var result: typeof(THEN, ELSE);
    //     if CONDITION then
    //         result := THEN;
    //     else
    //         result := ELSE;
    //     => result
    // }
    // ```
    //
    // The result type is therefore the common type of both branches.

    TEST_CASE(
        "The 'if' and 'else' statements must evaluate according to the boolean condition",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    if true then
        log1str("OK");

    if false then
        log1str("NOT OK");

    if true then
        log1str("OK");
    else
        log1str("NOT OK");

    if false then
        log1str("NOT OK");
    else
        log1str("OK");
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "OK", {}},
                    {core::Reporter::Level::INFO, "OK", {}},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }

    TEST_CASE("The 'if' and 'else' statements can be chained", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    if false then
        log1str("NOT OK");
    else if false then
        log1str("NOT OK");
    else if true then
        log1str("OK");
    else if false then
        log1str("NOT OK");
    else
        log1str("NOT OK");
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "OK", {}}}
            }
        );
    }

    TEST_CASE("The condition of an 'if' statement must be of type 'Bool'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    if 1 then
        log1str("NOT OK");
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Bool' but got 'Size'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 8)}
                }
            }
        );
    }

    TEST_CASE("An 'if' expression returns the value of the taken branch", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert (if true then 1 else 2) == 1;
    assert (if false then 1 else 2) == 2;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("An 'if' expression requires an 'else' branch", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: Size := if true then 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Unexpected token ';', check it and previous tokens for errors",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 34)}
                }
            }
        );
    }

    TEST_CASE("The branches of an 'if' expression must have a common type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: Size := if true then 1 else true;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Could not find common type for types 'Size' and 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 20)}
                }
            }
        );
    }
}
