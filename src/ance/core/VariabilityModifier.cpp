#include "VariabilityModifier.h"

#include <stdexcept>

ance::core::VariabilityModifier::operator Value() const
{
    return value_;
}

std::string ance::core::VariabilityModifier::toString() const
{
    switch (value_)
    {
        case VARIABLE:
            return "var";

        case INVARIABLE:
            return "";// Because this is the default, it has no textual representation.
    }

    throw std::logic_error("Invalid variability modifier");
}

bool ance::core::VariabilityModifier::isVariable() const
{
    return value_ == VARIABLE;
}
