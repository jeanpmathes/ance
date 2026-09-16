#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'Identifier' type represents identifiers used for names in the language.
    // It has no default value.

    TEST_CASE("'Identifier' is available as a core type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let identifier_type: Type := Identifier;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("'Identifier' has no default value", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: Identifier;
}
)ance",
                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level   = core::Reporter::Level::ERROR,
                          .content = "Cannot create default value for type 'Identifier'",
                          .location =
                              test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 16)}
                }
            }
        );
    }
}
