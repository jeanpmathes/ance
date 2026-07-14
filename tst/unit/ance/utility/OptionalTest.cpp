#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "ance/utility/Optional.h"
#include "ance/utility/Owners.h"

TEST_CASE("Optional can be empty", "[unit]")
{
    ance::utility::Optional<int> optional;

    CHECK_FALSE(optional.hasValue());
    CHECK(optional.valueOr(42) == 42);
}

TEST_CASE("Optional can contain a value", "[unit]")
{
    ance::utility::Optional optional = 7;

    REQUIRE(optional.hasValue());
    CHECK(*optional == 7);
    CHECK(optional.value() == 7);
    CHECK(optional.valueOr(42) == 7);
}

TEST_CASE("Optional transfers ownership when moved", "[unit]")
{
    ance::utility::Optional                            source = ance::utility::makeOwned<int>(7);
    ance::utility::Optional<ance::utility::Owned<int>> target = std::move(source);

    CHECK_FALSE(source.hasValue());
    REQUIRE(target.hasValue());
    REQUIRE(target->get() != nullptr);
    CHECK(**target == 7);
}
