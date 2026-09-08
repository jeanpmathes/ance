#include "Occurrence.h"

#include <stdexcept>

ance::core::Occurrence::operator Value() const
{
    return value_;
}

bool ance::core::Occurrence::isAtMostOnce() const
{
    return value_ == NOT_APPLICABLE || value_ == NEVER || value_ == AT_MOST_ONCE
        || value_ == EXACTLY_ONCE;
}

bool ance::core::Occurrence::isAtLeastOnce() const
{
    return value_ == NOT_APPLICABLE || value_ == EXACTLY_ONCE || value_ == AT_LEAST_ONCE
        || value_ == MORE_THAN_ONCE;
}

bool ance::core::Occurrence::isExactlyOnce() const
{
    return value_ == NOT_APPLICABLE || value_ == EXACTLY_ONCE;
}

std::string ance::core::Occurrence::toString() const
{
    switch (value_)
    {
        case NOT_APPLICABLE:
            return "not applicable";

        case NEVER:
            return "never";

        case AT_MOST_ONCE:
            return "at most once";

        case UNCONSTRAINED:
            return "unconstrained";

        case EXACTLY_ONCE:
            return "exactly once";

        case AT_LEAST_ONCE:
            return "at least once";

        case MORE_THAN_ONCE:
            return "more than once";
    }

    throw std::invalid_argument("Invalid occurrence");
}
