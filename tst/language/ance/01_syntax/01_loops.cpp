#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    TEST_CASE("All break statements must be within a loop", "[language]")
    {
        test::checkSource(test::SourceTest {
            .source = R"ance(
{
    break;
}
)ance",

            .expected_compilation = test::Compilation::FAILURE,
            .expected_output      = {{core::Reporter::Level::ERROR, "Break statement outside of loop", test::SourceLocation {test::MAIN_SOURCE_FILE, 3, 5}}}});
    }

    TEST_CASE("All continue statements must be within a loop", "[language]")
    {
        test::checkSource(test::SourceTest {
            .source = R"ance(
{
    continue;
}
)ance",

            .expected_compilation = test::Compilation::FAILURE,
            .expected_output = {{core::Reporter::Level::ERROR, "Continue statement outside of loop", test::SourceLocation {test::MAIN_SOURCE_FILE, 3, 5}}}});
    }
}
