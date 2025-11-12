#include "Temporary.h"

#include "ance/bbt/Value.h"
#include "ance/bbt/Node.h"

ance::cet::Temporary::Temporary() : value_(bbt::UnitValue::make())
{}

void ance::cet::Temporary::setValue(utility::Shared<bbt::Value> value)
{
    value_ = value;
}

ance::utility::Shared<ance::bbt::Value> ance::cet::Temporary::getValue()
{
    return value_;
}

ance::bbt::Value const& ance::cet::Temporary::getValue() const
{
    return *value_;
}
