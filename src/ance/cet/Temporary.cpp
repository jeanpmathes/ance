#include "Temporary.h"

#include <cassert>

#include "ance/bbt/Value.h"

#include "ance/cet/Address.h"
#include "ance/cet/ValueExtensions.h"

ance::cet::Temporary::Temporary(bbt::TypeContext& type_context) : value_(bbt::Unit::make(type_context)), type_context_(type_context) {}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::access()
{
    return LReference::make(Address(*this), value_->type(), type_context_);
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

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::read()
{
    return read({});
}

void ance::cet::Temporary::write(utility::Shared<bbt::Value> value)
{
    write(std::move(value), {});
}

bool ance::cet::Temporary::isDefined() const
{
    return true;
}
