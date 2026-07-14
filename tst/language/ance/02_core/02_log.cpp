#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    TEST_CASE("Strings can be logged to compiler output", "[language]")
    {
        test::checkSource(test::SourceTest {.source = R"ance(
                {
                    log1s("Hello, World!");
                }
)ance",

                                            .expected_compilation = test::Compilation::SUCCESS,
                                            .expected_output      = {{core::Reporter::Level::INFO, "Hello, World!"}}});
    }
}
