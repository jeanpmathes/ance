#include "AccessModifier.h"

ance::core::AccessModifier::operator Value() const
{
    return value_;
}

std::string ance::core::AccessModifier::toString() const
{
    switch (value_)
    {
        case PRIVATE_ACCESS:
            return "private";

        case PUBLIC_ACCESS:
            return "public";

        case EXTERN_ACCESS:
            return "extern";
    }

    return "unknown";
}
