#include "lang/AccessModifier.h"

#include "lang/utility/Storage.h"

lang::AccessModifier::operator Value() const
{
    return value_;
}

std::string lang::AccessModifier::toString() const
{
    switch (value_)
    {
        case AccessModifier::PRIVATE_ACCESS:
            return "private";

        case AccessModifier::PUBLIC_ACCESS:
            return "public";

        case AccessModifier::EXTERN_ACCESS:
            return "extern";
    }
}

void lang::AccessModifier::synchronize(lang::AccessModifier* access_modifier, Storage& storage)
{
    uint8_t value = access_modifier->value_;
    storage.sync(value);
    access_modifier->value_ = static_cast<Value>(value);
}
