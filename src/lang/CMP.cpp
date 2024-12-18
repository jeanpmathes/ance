#include "CMP.h"

#include <stdexcept>

#include "lang/utility/Storage.h"

lang::CMP::operator Value() const
{
    return value_;
}

bool lang::CMP::isRuntime() const
{
    return value_ == OPTIONAL_CMP || value_ == NO_CMP;
}

bool lang::CMP::isCompileTime() const
{
    return value_ == OPTIONAL_CMP || value_ == ONLY_CMP;
}

lang::CMP lang::CMP::strict() const
{
    if (value_ == OPTIONAL_CMP) return ONLY_CMP;

    return value_;
}

std::string lang::CMP::toString() const
{
    switch (value_)
    {
        case OPTIONAL_CMP:
            return "cmp?";
        case ONLY_CMP:
            return "cmp";
        case NO_CMP:
            return "";
        case INVALID:
            return "/* invalid cmp */";
    }
}

lang::CMP lang::CMP::operator&(lang::CMP other) const
{
    if (value_ == other.value_) return value_;

    bool cmp    = isCompileTime() && other.isCompileTime();
    bool no_cmp = isRuntime() && other.isRuntime();

    if (cmp && no_cmp) return OPTIONAL_CMP;

    if (cmp) return ONLY_CMP;

    if (no_cmp) return NO_CMP;

    return INVALID;
}

void lang::CMP::synchronize(lang::CMP* cmp, Storage& storage)
{
    uint8_t value = cmp->value_;
    storage.sync(value);
    cmp->value_ = static_cast<Value>(value);
}
