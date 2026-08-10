#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // Arrays can be used to create a sequence with a fixed number of values of the same
    // type. As such, an array type is constructed using the element type and a fixed
    // length. Arrays themselves can be constructed using the array constructor syntax,
    // which takes a sequence of elements. It allows specifying the array type, if that is
    // not done, the common type of all elements is used. Arrays can be accessed using the
    // subscript operator, which provides a reference to the accessed element. The
    // reference is of the same variability as the accessed array reference. Out-of-bounds
    // access must be detected during evaluation.

    TEST_CASE(
        "Array elements are initialized with the default value of the element type",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [Size; 3];

    assert a[0] == 0;
    assert a[2] == 0;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("The array type constructor expects an element type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [5; 3];
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Type' but got 'Size'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 13)}
                }
            }
        );
    }

    TEST_CASE("The array type constructor expects a size", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [Size; true];
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 19)}
                }
            }
        );
    }

    TEST_CASE("The array size can be the result of an expression", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [Size; 1 + 2];

    assert a[2] == 0;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("The array size can be zero", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [Size; 0];
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Array types can be nested", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [[Size; 2]; 3];

    assert a[0][0] == 0;
    assert a[2][1] == 0;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("Array access works with nested arrays as well", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [[Size; 2]; 2] := [[1, 2], [3, 4]];

    assert a[0][1] == 2;
    assert a[1][0] == 3;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "An array constructor infers its element type from its elements",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [1, 2, 3];

    assert a[1] == 2;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("An array constructor can declare its element type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [Size | 1, 2, 3];

    assert a[2] == 3;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "The types of the elements must match the specified element type",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [Size | 1, true, 3];
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 36)}
                }
            }
        );
    }

    TEST_CASE("The types of the elements must have a common type", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 2] := [1, true];
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Could not find common type for types 'Size' and 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 25)}
                }
            }
        );
    }

    TEST_CASE(
        "An array constructor with a declared element type can be empty",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 0] := [Size |];
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE(
        "An array constructor without a declared element type cannot be empty",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 0] := [];
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot infer element type of empty array constructor",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 3, 25)}
                }
            }
        );
    }

    TEST_CASE("Out-of-bounds subscript access is not allowed", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [1, 2, 3];

    assert a[3] == 0;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Subscript index 3 is out of bounds",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 14)}
                }
            }
        );
    }

    TEST_CASE("The subscript index value must be a size", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [1, 2, 3];

    assert a[true] == 1;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Expected type 'Size' but got 'Bool'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 14)}
                }
            }
        );
    }

    TEST_CASE(
        "It is not possible to use the subscript operator on non-array types",
        "[language]"
    )
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let x: Size := 5;

    assert x[0] == 5;
}
)ance",

                .expected_compilation = test::Compilation::FAILURE,
                .expected_output      = {
                    {core::Reporter::Level::ERROR,
                          "Cannot subscript value of type 'Size'",
                          test::SourceLocation::inPosition(test::MAIN_SOURCE_FILE, 5, 12)}
                }
            }
        );
    }

    TEST_CASE("It is possible to write to variable arrays", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [Size; 3] := [1, 2, 3];

    a[0] := 9;

    assert a[0] == 9;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("It is possible to write to variable nested arrays", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    var a: [[Size; 2]; 3] := [[1, 2], [3, 4], [5, 6]];

    a[2] := [0, 42];
    assert a[2][1] == 42;

    a[2][1] := 12;
    assert a[2][1] == 12;
}
)ance",

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }

    TEST_CASE("It is not possible to write to constant arrays", "[language]")
    {
        test::checkSource(
            test::SourceTest {
                .source = R"ance(
{
    let a: [Size; 3] := [1, 2, 3];

    a[0] := 9;
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
}
