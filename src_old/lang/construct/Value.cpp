#include "Value.h"

#include "lang/type/Type.h"

lang::Value::Value(lang::Type const& type) : type_(type) {}

lang::Type const& lang::Value::type() const
{
    return type_;
}
