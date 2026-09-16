#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Control flow within functions can be ended using the 'return' statement, which
    // causes immediate return from the function. The statement can also optionally be
    // supplied with a value which is used as the return value of the function. If the
    // function has a non-'Unit' return type, a return value must be supplied. If the
    // return type is the 'Unit' type, no return value is needed. The return value type
    // must always match the return type of the function.

    TEST_CASE(
        "Returning without a value is valid when the return type is 'Unit'",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    let result: Unit := f();
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f ()
{
    return;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("The 'Unit' literal does not need to be specified explicitly", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f ()
{
    return ();
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {.level   = core::Reporter::Level::WARNING,
                          .content = "The explicit unit literal return value can be omitted",
                          .location =
                              test::SourceLocation::inPosition("declaration.nc", 4, 12)}
                }
            }
        );
    }

    TEST_CASE(
        "Returning a value matching the function's return type is valid",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert f() == 42;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f () : Size
{
    return 42;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Returning without a value is invalid when the return type is not 'Unit'",
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
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f () : Size
{
    return;
}
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level    = core::Reporter::Level::ERROR,
                          .content  = "Not all paths return a value",
                          .location = test::SourceLocation::inPosition("declaration.nc", 2, 1)}
                }
            }
        );
    }

    TEST_CASE(
        "Using a return statement outside of a function is not allowed",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    return;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level   = core::Reporter::Level::ERROR,
                          .content = "Return statement outside of function",
                          .location =
                              test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 5)}
                }
            }
        );
    }

    TEST_CASE(
        "Code following a return statement in control flow is unreachable",
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
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f ()
{
    return;
    log1str("NOT OK");
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {.level    = core::Reporter::Level::WARNING,
                          .content  = "Unreachable code",
                          .location = test::SourceLocation::inPosition("declaration.nc", 5, 5)}
                }
            }
        );
    }

    TEST_CASE(
        "Code in lines after a return statement is not necessarily unreachable",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    f(true);
    f(false);
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f (condition: Bool)
{
    if condition then return;

    log1str("OK");
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {.level    = core::Reporter::Level::INFO,
                          .content  = "OK",
                          .location = {}}
                }
            }
        );
    }
}
