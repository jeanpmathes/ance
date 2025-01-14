#include "CustomType.h"

lang::CustomType::CustomType(lang::Accessibility accessibility) : accessibility_(accessibility) {}

bool lang::CustomType::isCustom() const
{
    return true;
}

bool lang::CustomType::isImported() const
{
    return accessibility_.isImported();
}

lang::Accessibility const& lang::CustomType::getAccessibility() const
{
    return accessibility_;
}
