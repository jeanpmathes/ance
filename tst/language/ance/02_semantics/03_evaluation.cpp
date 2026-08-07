#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language uses a potent compile-time evaluation system, which is essentially
    // interpretation at compile time. This is what allows it to make unordered scopes
    // possible, as it allows stopping evaluation whenever needed and resuming another
    // evaluation point.
    //
    // One other effect of this is that types become ordinary expressions during
    // compile-time. Types can be computed using functions, assigned to alternative names,
    // and parts of types can be filled in using computations.
    //
    // As a consequence of this evaluation model, types are value-based, and type
    // constructors generally create a new value, not simply return a reference to the
    // same type instance.

    TEST_CASE("Types can be read from local names", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source               = R"ance(
{
    let x_type: Type := String;
    let x: x_type := "Text";

    assert x == "Text";
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Types can be read from global names", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source             = R"ance(
{
    include("declarations.nc", here);

    let x: type := "Text";

    assert x == "Text";
}
)ance",
                .additional_sources = {{
                    "declarations.nc",
                    R"ance(
public type: Type := String;
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Types can be computed from functions", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source             = R"ance(
{
    include("declarations.nc", here);

    let x: compute_type("Text") := "Text";
    let y: compute_type("Truth") := true;

    assert x == "Text";
    assert y == true;
}
)ance",
                .additional_sources = {{
                    "declarations.nc",
                    R"ance(
public compute_type (input: String) : Type
{
    if input == "Text" then
        return String;
    else
        return Bool;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
