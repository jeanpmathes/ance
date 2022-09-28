#include "AddressType.h"

bool lang::AddressType::isAddressType() const
{
    return true;
}

StateCount lang::AddressType::getStateCount() const
{
    return SpecialCount::ABSTRACT;
}
