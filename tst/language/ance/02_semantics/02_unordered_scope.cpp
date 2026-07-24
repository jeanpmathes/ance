#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Unordered scopes do not define any specific order, instead any order that allows
    // to resolve all names may be chosen. During compile-time evaluation of declarations
    // and definitions, the evaluation of any element may be paused to first evaluate
    // any other element. Only a name that is fully defined may be resolved.
    //
    // All files except the first file are unordered scopes on the top level.
    //
    // If no evaluation order exists that satisfies resolution of all names, the compilation
    // must fail. This could, for example, be caused by a cyclical dependency chain.

    TEST_CASE(
        "A declaration can use a name declared below in the same unordered scope",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declarations.nc", here);

    log1str(second);
}
)ance",

                .additional_sources = {{
                    "declarations.nc",
                    R"ance(
public second: String := first;
public first: String := "first";
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "first"}}
            }
        );
    }

    TEST_CASE("A declaration that depends on itself is invalid", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declarations.nc", here);
}
)ance",

                .additional_sources = {{
                    "declarations.nc",
                    R"ance(
public a: String := a;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'a'",
                          test::SourceLocation::inPosition("declarations.nc", 2, 21)}
                }
            }
        );
    }

    TEST_CASE("Declarations forming a cyclical chain are invalid", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declarations.nc", here);
}
)ance",

                .additional_sources = {{
                    "declarations.nc",
                    R"ance(
public a: String := b;
public b: String := a;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'b'",
                          test::SourceLocation::inPosition("declarations.nc", 2, 21)},
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'a'",
                          test::SourceLocation::inPosition("declarations.nc", 3, 21)}
                }
            }
        );
    }
}
