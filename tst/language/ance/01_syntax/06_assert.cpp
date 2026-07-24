#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // An 'assert' statement evaluates a 'Bool' condition.
    // If the condition is 'true', evaluation continues normally.
    // If the condition is 'false', compilation fails and evaluation is stopped.

    TEST_CASE(
        "An 'assert' statement does not stop evaluation when its condition is true",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert true;

    log1str("OK");
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "OK", {}}}
            }
        );
    }

    TEST_CASE(
        "An 'assert' statement stops evaluation when its condition is false",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert false;

    log1str("NOT OK");
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Assertion failed",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 12)}
                }
            }
        );
    }
}
