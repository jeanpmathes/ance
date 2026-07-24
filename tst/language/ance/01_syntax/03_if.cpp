#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language allows checking of conditions using 'if' and 'else' statements.
    // This statement evaluates an expression that provides a value of type 'Bool'.
    // If the value is 'true', the first branch is executed, otherwise, the second branch is executed.
    // The second branch can be omitted, in which case none of the branches is evaluated on 'false'.

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
}
