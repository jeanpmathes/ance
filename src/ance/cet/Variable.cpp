#include "Variable.h"

ance::cet::Variable::Variable(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location)
    : identifier_(identifier)
    , type_(type)
    , is_final_(is_final)
    , location_(location)
{}

ance::core::Identifier const& ance::cet::Variable::name() const
{
    return identifier_;
}

ance::core::Type const& ance::cet::Variable::type() const
{
    return type_;
}

bool ance::cet::Variable::isFinal() const
{
    return is_final_;
}

ance::core::Location const& ance::cet::Variable::location() const
{
    return location_;
}

bool ance::cet::Variable::isDefined() const
{
    return value_.hasValue();
}

ance::utility::Shared<ance::bbt::Value> ance::cet::Variable::getValue()
{
    assert(isDefined());

    return value_.value();
}

void ance::cet::Variable::setValue(utility::Shared<bbt::Value> value)
{
    assert(!is_final_ || !isDefined());

    value_ = std::move(value);
}
