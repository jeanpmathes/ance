#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'Unit' type is a unit type. This means it has exactly one value, which
    // can be accessed using the unit literal '()'.

    TEST_CASE("Unit literals have type 'Unit'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(()) == Unit;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Default-initialized 'Unit' values are unit", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: Unit;
    assert value == ();
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("The unit value is equal itself", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert () == ();
    assert not (() /= ());
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
