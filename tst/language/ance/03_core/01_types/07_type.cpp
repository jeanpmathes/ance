#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The type 'Type' is the type of all types. Type names are the literals of the type
    // 'Type'. The type supports equality operators.

    TEST_CASE("Core types are values of type 'Type'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let unit: Type := Unit;
    let boolean: Type := Bool;
    let size: Type := Size;
    let half: Type := Half;
    let single: Type := Single;
    let double: Type := Double;
    let quad: Type := Quad;
    let string: Type := String;
    let identifier: Type := Identifier;
    let location: Type := Location;
    let function: Type := Function;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("'Type' is a value of type 'Type'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let type: Type := Type;
    assert typeof(typeof(())) == Type;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Type equality compares represented types", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert Unit == Unit;
    assert Unit /= Bool;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
