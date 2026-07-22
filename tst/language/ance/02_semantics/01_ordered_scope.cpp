#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Ordered scopes impose an order of declaration, which is the order of statements
    // within the scope. This means names can only be resolved after they have been
    // defined. If a name is defined multiple times, the most recent declaration is used.
    //
    // When declaring a name within a nested scope, this hides the outer name within the
    // nested scope. Hiding is only allowed when none of the previous statements of the
    // nested scope use that outer name. This serves to keep code more understandable.
    //
    // The main file is an ordered scope on the top level, as are the bodies of functions.

    TEST_CASE(
        "A defined name can be used afterwards in the same ordered scope",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: String := "value";
    log1s(x);
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {{core::Reporter::Level::INFO, "value"}}
            }
        );
    }

    TEST_CASE("A name cannot be used if it has not been defined earlier", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    log1s(x);

    let x: String := "value";
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot resolve name 'x'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 11)}
                }
            }
        );
    }

    TEST_CASE(
        "A nested ordered scope can declare a name that hides an enclosing declaration",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: String := "outer";
    log1s(x);

    {
        let x: Bool := true;
        log1b(x);
    }

    log1s(x);
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "outer"},
                    {core::Reporter::Level::INFO, "true"},
                    {core::Reporter::Level::INFO, "outer"}
                }
            }
        );
    }

    TEST_CASE("A nested ordered scope cannot hide an outer used name", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: String := "outer";

    {
        log1s(x);

        let x: String := "inner";
    }
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "outer"},
                    {core::Reporter::Level::ERROR,
                          "Declaring 'x' in this scope would block previous access to it "
                               "outside of the scope",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 8, 9)}
                }
            }
        );
    }
}
