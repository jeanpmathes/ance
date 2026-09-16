#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The 'String' type represents a sequence of codepoints and uses the empty string as
    // its default value. String values can be compared using the equality operators.

    TEST_CASE("String literals have type 'String'", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof("text") == String;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Default-initialized 'String' values are empty", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var value: String;
    assert value == "";
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("String equality compares text", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert "same" == "same";
    assert "left" /= "right";
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("String values preserve Unicode text", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    log1str("Grüße, 世界!");
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {.level = core::Reporter::Level::INFO, .content = "Grüße, 世界!"}
                }
            }
        );
    }
}
