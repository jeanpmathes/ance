#include "Intrinsic.h"

#include <utility>

ance::core::Intrinsic::Value ance::core::Intrinsic::value() const
{
    return value_;
}

ance::core::Identifier ance::core::Intrinsic::identifier() const
{
    return Identifier::make(toString());
}

std::string ance::core::Intrinsic::toString() const
{
    switch (value_)
    {
        case NO_OPERATION:
            return "nop";
        case DECLARE:
            return "declare";
        case RESOLVE:
            return "resolve";
        case GET_PARENT:
            return "get_parent";
        case B_2_STR:
            return "b2str";
        case LOG:
            return "log";
        case INCLUDE:
            return "include";
    }
}
