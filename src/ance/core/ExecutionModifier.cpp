#include "ExecutionModifier.h"

ance::core::ExecutionModifier::operator Value() const
{
    return value_;
}

std::string ance::core::ExecutionModifier::toString() const
{
    switch (value_)
    {
        case COMPILETIME_EXECUTION:
            return "compile";
        case RUNTIME_EXECUTION:
            return "runtime";
        case ANY_EXECUTION:
            return "";
    }

    return "unknown";
}
