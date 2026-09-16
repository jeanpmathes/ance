#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'Size' type represents non-negative integer values of not closer defined size.
    // It is always large enough to hold the maximum possible allocation size for a
    // machine. It supports arithmetic, relational, equality and bitwise operators.
    // Division and reminder by zero are invalid.

    TEST_CASE("Integer literals have type 'Size'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(42) == Size;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Default-initialized 'Size' values are zero", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: Size;
    assert value == 0;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Size arithmetic produces 'Size' values", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 5 + 3 == 8;
    assert 5 - 3 == 2;
    assert 5 * 3 == 15;
    assert 8 / 3 == 2;
    assert 8 % 3 == 2;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
    /* todo: bring these two tests back
    TEST_CASE("Dividing a 'Size' value by zero is invalid", "[language]")
    {
        test::checkSource(test::SourceTest {
            .source               = R"ance(
{
    let value: Size := 1 / 0;
}
)ance",
            .expected_compilation = test::Compilation::FAILURE,
            .expected_output = {{core::Reporter::Level::ERROR,
                                 "Division by zero",
                                 test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 24)}}
        });
    }

    TEST_CASE("Taking the remainder of a 'Size' value by zero is invalid", "[language]")
    {
        test::checkSource(test::SourceTest {
            .source               = R"ance(
{
    let value: Size := 1 % 0;
}
)ance",
            .expected_compilation = test::Compilation::FAILURE,
            .expected_output = {{core::Reporter::Level::ERROR,
                                 "Division by zero",
                                 test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 24)}}
        });
    }*/

    TEST_CASE("Bitwise negation inverts every bit of a 'Size' value", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert <not> <not> 42 == 42;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Size relational operators compare numeric values", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 1 < 2;
    assert 1 <= 1;
    assert 2 > 1;
    assert 2 >= 2;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Size equality compares numeric values", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 42 == 42;
    assert 42 /= 7;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
