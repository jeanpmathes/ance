#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Functions are values of the 'Function' type and can be created using lambdas or
    // function declarations. Function values can be stored and called, but the type has
    // no default value.

    TEST_CASE("Lambda expressions produce values of type 'Function'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(\() { let value: Unit := (); }) == Function;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Function declarations bind values of type 'Function'", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);
    let function: Function := f;
}
)ance",
                .additional_sources =
                    {{.relative_path = "declaration.nc", .content = R"ance(
public f ()
{}
)ance"}},
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Stored function values can be called", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let function: Function := \() : Size => 42;
    assert function () == 42;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("'Function' has no default value", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: Function;
}
)ance",
                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level   = core::Reporter::Level::ERROR,
                          .content = "Cannot create default value for type 'Function'",
                          .location =
                              test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 16)}
                }
            }
        );
    }
}
