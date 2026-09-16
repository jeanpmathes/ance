#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The language offers four different floating-point types, which are 'Half',
    // 'Single', 'Double' and 'Quad', following IEEE conventions. Each precision uses zero
    // as the default value and supports arithmetic, relational and equality operators.

    TEST_CASE("Floating-point literal suffixes select their precision", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(1.0h) == Half;
    assert typeof(1.0s) == Single;
    assert typeof(1.0d) == Double;
    assert typeof(1.0q) == Quad;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point literals can omit the integer part", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(.5h) == Half;
    assert .5h == 0.5h;
    assert typeof(.5s) == Single;
    assert .5s == 0.5s;
    assert typeof(.5d) == Double;
    assert .5d == 0.5d;
    assert typeof(.5q) == Quad;
    assert .5q == 0.5q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point literals accept explicit leading signs", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(+1.5h) == Half;
    assert typeof(-1.5h) == Half;
    assert +1.5h == 1.5h;
    assert -1.5h == 0.0h - 1.5h;
    assert typeof(+1.5s) == Single;
    assert typeof(-1.5s) == Single;
    assert +1.5s == 1.5s;
    assert -1.5s == 0.0s - 1.5s;
    assert typeof(+1.5d) == Double;
    assert typeof(-1.5d) == Double;
    assert +1.5d == 1.5d;
    assert -1.5d == 0.0d - 1.5d;
    assert typeof(+1.5q) == Quad;
    assert typeof(-1.5q) == Quad;
    assert +1.5q == 1.5q;
    assert -1.5q == 0.0q - 1.5q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point literals accept signed decimal exponents", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(1.5e-1h) == Half;
    assert typeof(1.5e+1h) == Half;
    assert 1.5e-1h == 0.15h;
    assert 1.5e+1h == 15.0h;
    assert typeof(1.5e-1s) == Single;
    assert typeof(1.5e+1s) == Single;
    assert 1.5e-1s == 0.15s;
    assert 1.5e+1s == 15.0s;
    assert typeof(1.5e-1d) == Double;
    assert typeof(1.5e+1d) == Double;
    assert 1.5e-1d == 0.15d;
    assert 1.5e+1d == 15.0d;
    assert typeof(1.5e-1q) == Quad;
    assert typeof(1.5e+1q) == Quad;
    assert 1.5e-1q == 0.15q;
    assert 1.5e+1q == 15.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Zero floating-point literals accept very large decimal exponents",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert typeof(0.0e999999h) == Half;
    assert 0.0e999999h == 0.0h;
    assert typeof(0.0e999999s) == Single;
    assert 0.0e999999s == 0.0s;
    assert typeof(0.0e999999d) == Double;
    assert 0.0e999999d == 0.0d;
    assert typeof(0.0e999999q) == Quad;
    assert 0.0e999999q == 0.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Default-initialized floating-point values are zero", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    var half: Half;
    var single: Single;
    var double: Double;
    var quad: Quad;

    assert half == 0.0h;
    assert single == 0.0s;
    assert double == 0.0d;
    assert quad == 0.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point arithmetic preserves precision", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 6.0h + 2.0h == 8.0h;
    assert 6.0h - 2.0h == 4.0h;
    assert 6.0h * 2.0h == 12.0h;
    assert 6.0h / 2.0h == 3.0h;
    assert 6.0s + 2.0s == 8.0s;
    assert 6.0s - 2.0s == 4.0s;
    assert 6.0s * 2.0s == 12.0s;
    assert 6.0s / 2.0s == 3.0s;
    assert 6.0d + 2.0d == 8.0d;
    assert 6.0d - 2.0d == 4.0d;
    assert 6.0d * 2.0d == 12.0d;
    assert 6.0d / 2.0d == 3.0d;
    assert 6.0q + 2.0q == 8.0q;
    assert 6.0q - 2.0q == 4.0q;
    assert 6.0q * 2.0q == 12.0q;
    assert 6.0q / 2.0q == 3.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point remainder follows IEEE semantics", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 7.0h % 4.0h == -1.0h;
    assert 7.0s % 4.0s == -1.0s;
    assert 7.0d % 4.0d == -1.0d;
    assert 7.0q % 4.0q == -1.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point negation changes the sign", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert -(1.0h) == -1.0h;
    assert -(1.0s) == -1.0s;
    assert -(1.0d) == -1.0d;
    assert -(1.0q) == -1.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Floating-point relational operators compare numeric values", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 1.0h < 2.0h;
    assert 1.0s <= 1.0s;
    assert 2.0d > 1.0d;
    assert 2.0q >= 2.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Floating-point equality compares values of the same precision",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    assert 1.0h == 1.0h;
    assert 1.0h /= 2.0h;
    assert 1.0s == 1.0s;
    assert 1.0s /= 2.0s;
    assert 1.0d == 1.0d;
    assert 1.0d /= 2.0d;
    assert 1.0q == 1.0q;
    assert 1.0q /= 2.0q;
}
)ance",
                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "Floating-point operators reject operands of different precisions",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source               = R"ance(
{
    let value: Half := 1.0h + 1.0s;
}
)ance",
                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {.level = core::Reporter::Level::ERROR,
                          .content =
                              "Operator '+' is not defined for types 'Half' and 'Single'",
                          .location =
                              test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 24)}
                }
            }
        );
    }
}
