#include <compare>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"

namespace ance::core
{
    TEST_CASE("Identifier preserves its interned text", "[unit]")
    {
        std::string const original_text = "identifier";
        std::string       source_text   = original_text;

        Identifier const identifier = Identifier::make(source_text, Location::nowhere());

        source_text.assign("changed");

        CHECK(identifier.text() == original_text);
    }

    TEST_CASE("Identifier comparison ignores source locations", "[unit]")
    {
        Identifier const first  = Identifier::make("same", Location::simple(1, 1, 0));
        Identifier const second = Identifier::make("same", Location::simple(9, 7, 2));

        CHECK((first <=> second) == std::weak_ordering::equivalent);
    }

    TEST_CASE("Identifier can be empty", "[unit]")
    {
        Identifier const identifier = Identifier::empty();

        CHECK(identifier.isEmpty());
        CHECK(identifier.text().empty());
        CHECK(identifier.location().isProject());
    }
}
