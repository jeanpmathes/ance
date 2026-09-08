#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Lambda expression can be used to create anonymous functions, and they expand
    // to anonymous function constructor calls. Lambdas do not support any capture
    // of names of ordered scopes.
    //
    // Lambda expressions support two declaration styles, one with an expression, the other
    // with statements. In the case of expressions, the result of the expression is also
    // the return value.
    //
    // All lambdas have a return type, but it is possible to omit its declaration.
    // In that case, the return type is 'Unit'.
    //
    // Lambdas can declare zero or more parameters, which become names bound in the
    // local function scope. As the function scope is a local scope, name hiding is
    // allowed in functions as well but causes a warning.

    TEST_CASE(
        "A lambda expression with an expression body can be called and returns a value",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert (\(x: Size): Size => x * 2)(21) == 42;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A lambda expression with a statement body can be called and returns a value",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size): Size { return x * 2; };
    assert f(21) == 42;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A lambda expression without a declared return type can be called and returns no "
        "the unit value",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size) { assert x == 5; };
    let result: Unit := f(5);
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A lambda expression cannot access names from the surrounding scope",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let value: Size := 5;
    let f: Function := \(x: Size) { assert value == 5; };
    f(1);
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'value'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 4, 44)}
                }
            }
        );
    }

    TEST_CASE(
        "Calling a lambda with the wrong number of arguments is not alowed",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size): Size => x;
    assert f(1, 2) == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Call to 'Lambda'0' with wrong number of arguments: expected 1 but "
                               "got 2",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 4, 12)}
                }
            }
        );
    }

    TEST_CASE(
        "Calling a lambda with an argument of the wrong type is not allowed",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size): Size => x;
    assert f(true) == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 4, 14)}
                }
            }
        );
    }

    TEST_CASE(
        "A lambda parameter's type expression must evaluate to a type",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: 5): Size => x;
    assert f(1) == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Type' but got 'Size'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 29)}
                }
            }
        );
    }

    TEST_CASE("A lambda's return type expression must evaluate to a type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size): true => x;
    assert f(1) == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Type' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 36)}
                }
            }
        );
    }

    TEST_CASE("A lambda parameter cannot be assigned to", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size): Size { x := 1; return x; };
    assert f(5) == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Can only store to variable reference values",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 43)}
                }
            }
        );
    }

    TEST_CASE(
        "A 'break' statement in a lambda's body outside of a loop is not allowed",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    loop
    {
        let f: Function := \(x: Size) { break; };
        f(1);
    }
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Break statement outside of loop",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 41)}
                }
            }
        );
    }

    TEST_CASE(
        "A lambda parameter that hides an earlier parameter with the same name causes a "
        "warning",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \(x: Size, x: Size): Size => x;
    assert f(1, 2) == 2;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::WARNING,
                          "Parameter 'x' hides earlier parameter",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 35)}
                }
            }
        );
    }

    TEST_CASE(
        "A lambda expression with a statement body can be invoked inline",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert (\(x: Size): Size { return x * 2; })(21) == 42;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Lambdas with a non-'Unit' return type require a return statement",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let f: Function := \() : Size { let value: Size := 42; };
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Not all paths return a value",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 24)}
                }
            }
        );
    }
}
