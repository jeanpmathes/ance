#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'Location' type represents a location in source code. The core value 'nowhere'
    // represents no source location, while each 'here' expression evaluates to its own
    // location. Default-created locations compare equal to each other.

    TEST_CASE("'here' expressions have type 'Location'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(here) == Location;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("'nowhere' has type 'Location'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let location: Location := nowhere;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Two 'nowhere' values are equal", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert nowhere == nowhere;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Two default-created 'Location' values are equal", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var first: Location;
    var second: Location;

    assert first == second;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Two separate 'here' expressions are unequal", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert here /= here;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
