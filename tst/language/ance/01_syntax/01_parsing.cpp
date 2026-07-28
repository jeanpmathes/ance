#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Invalid syntax must be rejected with a sensible diagnostic instead of crashing the compiler.

    TEST_CASE(
        "Invalid syntax is rejected with a sensible error instead of crashing",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    @#$%
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Unexpected character",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 5)}
                }
            }
        );
    }
}
