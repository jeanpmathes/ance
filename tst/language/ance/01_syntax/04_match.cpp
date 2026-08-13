#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language allows comparing a value against a set of patterns using the 'match'
    // statement, which is similar to, for example, the switch statement of many
    // languages. The patterns apply as if checked in order, with (only) the first
    // matching pattern being chosen. The used patterns must match the type of the matched
    // value. The 'default' pattern can be used to match any value.
    //
    // Any match statement must be exhaustive, which means all values are covered by at
    // least one pattern.
    //
    // Similar to 'match' statements, 'match' expressions can be used to produce a value.
    // These expressions are expanded to a block containing a 'match' statement.
    // As such, for the following 'match' expression...
    // ```ance
    // match CONDITION with { ( PATTERN => EXPRESSION )... }
    // ```
    // ...the equivalent expansion is:
    //
    // ```ance
    // {
    //     var result: typeof(EXPRESSION...);
    //     match CONDITION with
    //     {
    //         ( PATTERN => result := EXPRESSION; )...
    //     }
    //     => result
    // }
    // ```
    //
    // The result type is therefore the common type of all cases.

    TEST_CASE(
        "A 'match' statement executes the first matching case or the default case",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 2 with
    {
        1 => log1str("NOT OK");
        2 | 3 => log1str("OK");
        default => log1str("NOT OK");
    }

    match 4 with
    {
        1 => log1str("NOT OK");
        2 | 3 => log1str("NOT OK");
        default => log1str("OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::INFO, "OK", {}},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }

    TEST_CASE(
        "A 'match' statement pattern must have the type of the matched value",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 1 with
    {
        true => log1str("NOT OK");
        default => log1str("NOT OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 9)}
                }
            }
        );
    }

    TEST_CASE("A 'match' statement must be exhaustive", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 1 with
    {
        1 => log1str("OK");
        2 => log1str("NOT OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Match does not cover all possible states of type 'Size'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 5)}
                }
            }
        );
    }

    TEST_CASE(
        "A 'match' expression produces the value of the first matching case or the "
        "default "
        "case",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    assert (match 2 with
    {
        1 => 10,
        2 | 3 => 20,
        default => 30
    }) == 20;

    assert (match 4 with
    {
        1 => 10,
        2 | 3 => 20,
        default => 30
    }) == 30;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("The results of a 'match' expression must have a common type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let value: Size := match 1 with
    {
        1 => 10,
        default => true
    };
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Could not find common type for types 'Size' and 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 24)}
                }
            }
        );
    }

    TEST_CASE(
        "A 'match' pattern covered by a preceding pattern causes a warning",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 1 with
    {
        1 => log1str("OK");
        1 => log1str("NOT OK");
        default => log1str("NOT OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::WARNING,
                          "Pattern not reachable",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 6, 9)},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }

    TEST_CASE(
        "A 'match' pattern covered by a preceding pattern in the same casecauses a "
        "warning",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 1 with
    {
        1 | 2 | 1 => log1str("OK");
        default => log1str("NOT OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::WARNING,
                          "Pattern not reachable",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 17)},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }

    TEST_CASE(
        "A 'match' pattern after the default pattern causes a warning",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    match 1 with
    {
        default => log1str("OK");
        1 => log1str("NOT OK");
    }
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {
                    {core::Reporter::Level::WARNING,
                          "Pattern not reachable",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 6, 9)},
                    {core::Reporter::Level::INFO, "OK", {}}
                }
            }
        );
    }
}
