#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language allows declaration of loops using the 'loop' keyword.
    // The loop keyword repeats the contained statement forever, other control flow constructs are needed in combination.
    // Two important control flow statements in this context are 'break' and 'continue', which can only be used within loops.
    // The 'break' statement causes the control flow to leave the innermost loop.
    // The 'continue' statement causes the control flow to begin a new iteration of the loop.
    // Both statements do not have to be immediately within the loop but can be further nested.

    TEST_CASE(
        "The 'break' statement can be used to break out of the inner-most loop",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    loop break;

    loop
    {
        log1str("A");
        break;
    }

    loop
    {
        {
            log1str("B");
            break;
        }
    }

    log1str("C");
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "A", {}},
                    {core::Reporter::Level::INFO, "B", {}},
                    {core::Reporter::Level::INFO, "C", {}}
                }
            }
        );
    }

    TEST_CASE("A 'break' not contained within a loop is invalid", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    break;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Break statement outside of loop",
                          test::SourceLocation {test::MAIN_SOURCE_FILE, 3, 5}}
                }
            }
        );
    }

    TEST_CASE("A 'continue' not contained within a loop is invalid", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    continue;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Continue statement outside of loop",
                          test::SourceLocation {test::MAIN_SOURCE_FILE, 3, 5}}
                }
            }
        );
    }
}
