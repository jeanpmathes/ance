#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // In unordered scopes, name declarations can be used to bind names.
    // These declarations have an access modifier, a type and optionally an initializer.
    // If no initializer is provided, the default value of the given type is used.
    // The initializer can be any expression but cannot access the name that is being declared.

    TEST_CASE("A name declaration binds an initialized value to a name", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert value == 42;
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
public value: Size := 42;
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A name declaration's initializer must match the declared type",
        "[language]"
    )
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
public value: Size := true;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition("declaration.nc", 2, 1)}
                }
            }
        );
    }

    TEST_CASE(
        "A name declaration without an initializer uses the default value",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert value == 0;
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
public value: Size;
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("A name declaration's initializer can be any expression", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert value == 52;
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
public compute(): Size
{
    return 6 * 7;
}

public value: Size := compute() + 10;
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("A name declared in an unordered scope cannot be assigned to", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    value := 2;
}
)ance",

                .additional_sources = {{
                    "declaration.nc",
                    R"ance(
public value: Size := 1;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Can only store to variable reference values",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 5)}
                }
            }
        );
    }

    TEST_CASE(
        "A name declaration's initializer cannot access the name being declared",
        "[language]"
    )
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
public value: Size := value;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'value'",
                          test::SourceLocation::inPosition("declaration.nc", 2, 23)}
                }
            }
        );
    }

    TEST_CASE(
        "A name declaration's type expression must evaluate to a type",
        "[language]"
    )
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
public value: 12 := 42;
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Type' but got 'Size'",
                          test::SourceLocation::inPosition("declaration.nc", 2, 15)}
                }
            }
        );
    }
}
