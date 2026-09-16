#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'Bool' type is used to represent boolean values of truth. It has two values,
    // which can be accessed using the 'true' and 'false' literals. By default, a boolean
    // value is 'false'.

    TEST_CASE("Boolean literals have type 'Bool'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(true) == Bool;
    assert typeof(false) == Bool;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Default-initialized 'Bool' values are false", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: Bool;
    assert value == false;
    assert not value;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Logical negation inverts boolean values", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert not false;
    assert not (not true);
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Boolean equality distinguishes 'true' and 'false'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert true == true;
    assert false == false;
    assert true /= false;
    assert false /= true;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
