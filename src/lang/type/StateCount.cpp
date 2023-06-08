#include "StateCount.h"

#include <cassert>

StateCount::StateCount(size_t count) : count_(count)
{
    assert(count != 0 && "State count cannot be zero.");
}

StateCount::StateCount(SpecialCount count) : count_(count) {}

Optional<size_t> StateCount::count() const
{
    if (auto count = std::get_if<size_t>(&count_)) return *count;

    return std::nullopt;
}

Optional<SpecialCount> StateCount::special() const
{
    if (auto count = std::get_if<SpecialCount>(&count_)) return *count;

    return std::nullopt;
}

bool StateCount::isUnit() const
{
    return count().valueOr(0) == 1;
}

bool StateCount::isCountable() const
{
    if (count().hasValue()) return true;

    return special().value() == SpecialCount::PLATFORM_DEPENDENT;
}

bool StateCount::isAbstract() const
{
    if (count().hasValue()) return false;

    return special().value() == SpecialCount::ABSTRACT;
}

static Optional<SpecialCount> getCommonSpecial(StateCount const& lhs, StateCount const& rhs)
{
    auto lhs_special = lhs.special();
    auto rhs_special = rhs.special();

    if (lhs_special.hasValue() && rhs_special.hasValue()) { return std::max(lhs_special.value(), rhs_special.value()); }

    if (lhs_special.hasValue()) return lhs_special.value();

    if (rhs_special.hasValue()) return rhs_special.value();

    return std::nullopt;
}

StateCount StateCount::operator*(StateCount const& other) const
{
    auto common_special = getCommonSpecial(*this, other);

    if (common_special.hasValue()) return common_special.value();

    return count().value() * other.count().value();
}

StateCount StateCount::operator+(StateCount const& other) const
{
    auto common_special = getCommonSpecial(*this, other);

    if (common_special.hasValue()) return common_special.value();

    return count().value() + other.count().value();
}

StateCount StateCount::unit()
{
    return 1;
}
