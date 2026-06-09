#include "Temporary.h"

#include <cassert>

#include "ance/bbt/Value.h"

#include "ance/cet/Address.h"
#include "ance/cet/ValueExtensions.h"

ance::cet::Temporary::Temporary(bbt::TypeContext& type_context) : value_(bbt::Unit::make(type_context)), type_context_(type_context) {}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::access()
{
    return Reference::make(Address(*this), value_->type(), core::VariabilityModifier::INVARIABLE, type_context_);
}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::read(std::vector<size_t> const& indices)
{
    auto result = load(value_, indices, type_context_);
    assert(result.hasValue());

    return result.value();
}

void ance::cet::Temporary::write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices)
{
    if (indices.empty())
    {
        value_ = std::move(value);
        return;
    }

    auto result = store(value_, indices, std::move(value), type_context_);
    assert(result.hasValue());

    value_ = result.value();
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

ance::bbt::Type const& ance::cet::Temporary::type() const
{
    return value_->type();
}
