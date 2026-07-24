#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    // The core library offers the include function of type 'String -> Unit', which is a compiletime function.
    // It causes the included file to be evaluated as well, and it is also the main mechanism for writing programs which
    // span over multiple files.
    //
    // Inclusion neither requires immediate evaluation of the included file, nor does it require the current file
    // to be completely evaluated first. It uses the resolve-based evaluation order.

    TEST_CASE(
        "Additional source files can be included using the include function",
        "[language]"
    )
    {
        test::checkSources(
            test::SourcesTest {
                .source = R"ance(
{
    include("first.nc", here);
    include("nested/second.nc", here);

    assert first == "first";
    assert second == "second";
}
)ance",

                .additional_sources =
                    {{
                         "first.nc",
                         R"ance(
public first: String := "first";
)ance",
                     },
                     {
                         "nested/second.nc",
                         R"ance(
public second: String := "second";
)ance",
                     }},

                .expected_compilation = test::Compilation::SUCCESS,
                .expected_output      = {}
            }
        );
    }
}
