#include <memory>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "ance/utility/Owners.h"

namespace
{
    struct Value
    {
        explicit Value(int const value) : value(value) {}

        [[nodiscard]] int doubled() const
        {
            return value * 2;
        }

        int value;
    };

    struct Base
    {
        virtual ~Base() = default;

        int value = 0;
    };

    struct Derived final : Base
    {
        explicit Derived(int const value)
        {
            this->value = value;
        }
    };
}

namespace ance::utility
{
    TEST_CASE("Owned constructs and exposes a value", "[unit]")
    {
        Owned<Value> value = ance::utility::makeOwned<Value>(7);

        REQUIRE(value.get() != nullptr);
        CHECK((*value).value == 7);
        CHECK(value->doubled() == 14);
    }

    TEST_CASE("Owned transfers exclusive ownership when moved", "[unit]")
    {
        Owned<Value> source  = ance::utility::makeOwned<Value>(7);
        Value* const address = source.get();

        Owned<Value> target = std::move(source);

        CHECK(source.get() == nullptr);
        CHECK(target.get() == address);
    }

    TEST_CASE("Owned can release its value", "[unit]")
    {
        std::unique_ptr<Value> released(unwrap(ance::utility::makeOwned<Value>(7)));

        REQUIRE(released != nullptr);
        CHECK(released->value == 7);
    }

    TEST_CASE("Shared copies refer to the same value", "[unit]")
    {
        Shared<Value> first  = ance::utility::makeShared<Value>(7);
        Shared<Value> second = first;

        second->value = 9;

        CHECK(first == second);
        CHECK(first->value == 9);
    }

    TEST_CASE("Shared supports polymorphic inspection and casting", "[unit]")
    {
        Shared<Derived> derived = ance::utility::makeShared<Derived>(7);
        Shared<Base>    base    = derived;

        REQUIRE(base.is<Derived>());

        Shared<Derived> downcast = base.as<Derived>();

        CHECK(downcast.get() == derived.get());
        CHECK(downcast->value == 7);
    }
}
