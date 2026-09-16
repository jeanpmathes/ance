#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // In unordered scopes, function declarations can be used to bind functions to names.
    // These declarations have an access modifier, a signature and a function body.
    // They expand into a name declaration with a function constructor in the initializer.
    // As such, declaring a name and assigning a lambda is equivalent to declaring a function.

    TEST_CASE("A function declaration binds a callable value to a name", "[language]")
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert compute() == 42;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public compute () : Size
{
    return 6 * 7;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A function declaration can declare parameters that are used in the body",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert add(21, 21) == 42;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public add (a: Size, b: Size) : Size
{
    return a + b;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Declaring a second function with the same name as an earlier function "
        "declaration is not allowed",
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
public compute () : Size
{
    return 1;
}

public compute () : Size
{
    return 2;
}
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level    = core::Reporter::Level::ERROR,
                          .content  = "Name 'compute' is already defined in this scope",
                          .location = test::SourceLocation::inPosition("declaration.nc", 7, 1)}
                }
            }
        );
    }

    TEST_CASE(
        "A declared function can be read like a variable holding a function value",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    let f: Function := compute;
    assert f() == 42;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public compute () : Size
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
        "A function declared in an unordered scope can call another such function",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert quarter(40) == 10;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public quarter (x: Size) : Size
{
    return half(half(x));
}

public half (x: Size) : Size
{
    return x / 2;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A function parameter that hides an earlier parameter with the same name causes "
        "a warning",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert f(1, 2) == 2;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public f (x: Size, x: Size) : Size
{
    return x;
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {.level   = core::Reporter::Level::WARNING,
                          .content = "Parameter 'x' hides earlier parameter",
                          .location =
                              test::SourceLocation::inPosition("declaration.nc", 2, 20)}
                }
            }
        );
    }

    TEST_CASE(
        "A function parameter's type expression must evaluate to a type",
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
public f (x: 5) : Size
{
    return x;
}
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level   = core::Reporter::Level::ERROR,
                          .content = "Expected type 'Type' but got 'Size'",
                          .location =
                              test::SourceLocation::inPosition("declaration.nc", 2, 14)}
                }
            }
        );
    }

    TEST_CASE("A function's return type expression must evaluate to a type", "[language]")
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
public f (x: Size) : true
{
    return x;
}
)ance",
                }},

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level   = core::Reporter::Level::ERROR,
                          .content = "Expected type 'Type' but got 'Bool'",
                          .location =
                              test::SourceLocation::inPosition("declaration.nc", 2, 22)}
                }
            }
        );
    }

    TEST_CASE(
        "A function declared in an unordered scope can call itself recursively",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("declaration.nc", here);

    assert factorial(5) == 120;
}
)ance",

                .additional_sources = {{
                    .relative_path = "declaration.nc",
                    .content       = R"ance(
public factorial (n: Size) : Size
{
    if n == 0 then return 1;
    return n * factorial(n - 1);
}
)ance",
                }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Functions with a non-'Unit' return type require a return statement",
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
{}
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
        "Functions with a non-'Unit' return type require a return statement in all paths",
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
    if true then return 42;
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
}
