#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Local name bindings are declared using 'let' and 'var'.
    // The 'let' keyword declares a constant, while 'var' declares a variable.
    // This means when accessing, the type is '&T' or '&var T' respectively.
    // Only 'var' allows reassigning, but redeclaring is always possible.

    TEST_CASE("A 'let' statement binds an initialized value to a name", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let message: String := "value";

    assert message == "value";
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("A 'let' statement must have an initializer", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let message: String;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Constants must be assigned a value on declaration",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 5)}
                }
            }
        );
    }

    TEST_CASE(
        "Writing to a name declared by a 'let' statement is not allowed",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let value: Size := 12;

    value := 42;
}
)ance",

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
        "A 'var' statement binds an initialized value to a name and can be changed "
        "afterwards",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var value: Size := 1;
    value := value + 2;

    assert value == 3;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "A 'var' statement without initializer uses the default value",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var value: Size;
    value := value + 2;

    assert value == 2;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
