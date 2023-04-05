#include "CustomType.h"

lang::CustomType::CustomType(bool is_imported) : is_imported_(is_imported) {}

bool lang::CustomType::isCustom() const
{
    return true;
}

bool lang::CustomType::isImported() const
{
    return is_imported_;
}
