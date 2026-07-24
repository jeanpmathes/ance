#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The log functions serve to log compiler output during compiletime.
    // All variants of the log functions create messages of level 'INFO'.
    // A multitude of versions exists:
    // log1str: 'String -> Unit'

    TEST_CASE("Intrinsic 'log1str' logs a string", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    log1str("Hello, World!");
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "Hello, World!"}}
            }
        );
    }
}
