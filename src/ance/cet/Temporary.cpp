#include "Temporary.h"

#include <cassert>

#include "ance/bbt/Value.h"

#include "ance/cet/Address.h"
#include "ance/cet/ValueExtensions.h"

ance::cet::Temporary::Temporary() : value_(bbt::Unit::make())
{}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::access()
{
    return LReference::make(Address(*this));
}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::read(std::vector<size_t> const& indices)
{
    assert(indices.empty());

    return value_;
}

void ance::cet::Temporary::write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices)
{
    assert(indices.empty());

    value_ = std::move(value);
}

bool ance::cet::Temporary::isDefined() const
{
    return true;
}
