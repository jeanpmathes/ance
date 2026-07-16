#include <catch2/catch_test_macros.hpp>

#include "ance/core/Location.h"

namespace ance::core
{
    TEST_CASE("Location distinguishes special location kinds", "[unit]")
    {
        Location const nowhere = Location::nowhere();
        Location const project = Location::project();
        Location const core    = Location::core();
        Location const file    = Location::file(7);

        CHECK(nowhere.isNowhere());
        CHECK(project.isProject());
        CHECK(core.isCore());
        CHECK(file.isFile());
        CHECK(file.fileIndex() == 7);
    }

    TEST_CASE("Simple Location describes one source position", "[unit]")
    {
        Location const location = Location::simple(2, 3, 4);

        CHECK(location.line() == 2);
        CHECK(location.column() == 3);
        CHECK(location.lineEnd() == 2);
        CHECK(location.columnEnd() == 3);
        CHECK(location.fileIndex() == 4);
        CHECK(location.isSingleLine());
    }

    TEST_CASE("Location exposes its first and last positions", "[unit]")
    {
        Location const location(2, 3, 4, 5, 6);

        CHECK(location.first() == ance::core::Location::simple(2, 3, 6));
        CHECK(location.last() == ance::core::Location::simple(4, 5, 6));
    }

    TEST_CASE("Location extends to cover another range in the same file", "[unit]")
    {
        Location location(2, 3, 4, 5, 6);

        location.extend(Location(1, 4, 5, 2, 6));

        CHECK(location == ance::core::Location(1, 4, 5, 2, 6));
    }

    TEST_CASE("Location extends to cover its entire file", "[unit]")
    {
        Location location(2, 3, 4, 5, 6);

        location.extend(Location::file(6));

        CHECK(location == ance::core::Location::file(6));
    }

    TEST_CASE("Location does not extend across different files", "[unit]")
    {
        Location       location(2, 3, 4, 5, 6);
        Location const original = location;

        location.extend(Location(1, 4, 5, 2, 7));

        CHECK(location == original);
    }
}
