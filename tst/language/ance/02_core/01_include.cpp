#include "SourceTest.h"

#include <catch2/catch_test_macros.hpp>

namespace ance
{
    TEST_CASE("Additional source files can be included using the include function", "[language]")
    {
        test::checkSources(test::SourcesTest {.source = R"ance(
{
    include("first.nc", here);
    include("nested/second.nc", here);
}
)ance",

                                              .additional_sources = {{
                                                                         "first.nc",
                                                                         R"ance(
public first: Bool := true;
)ance",
                                                                     },
                                                                     {
                                                                         "nested/second.nc",
                                                                         R"ance(
public second: Bool := false;
)ance",
                                                                     }},

                                              .expected_compilation = test::Compilation::SUCCESS,
                                              .expected_output      = {}});
    }
}
