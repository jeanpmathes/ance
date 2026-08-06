#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Unordered scopes allow different kinds of declarations. The most basic kind of
    // declaration is the 'do' declaration. It contains a statement, which can be a block
    // and evaluates it at some point during compile time evaluation. There is no guaranteed
    // order of evaluation of 'do' declarations.

    TEST_CASE("A 'do' declaration evaluates its statement", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
do log1str("OK");
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "OK", {}}}
            }
        );
    }

    TEST_CASE("A 'do' declaration can use names declared outside of it", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
do assert value == 42;

public value: Size := 42;
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("All 'do' declarations in an unordered scope are evaluated", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
do
{
    log1str("OK")
}

do log1str("OK");
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "OK", {}},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }
}
