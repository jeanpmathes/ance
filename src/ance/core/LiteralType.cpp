#include "LiteralType.h"

#include <stdexcept>

namespace ance::core
{
    LiteralType::operator Value() const
    {
        return value_;
    }

    std::string LiteralType::toString() const
    {
        switch (value_)
        {
            case Bool: return "Bool";
            case Unit: return "Unit";
            case Size: return "Size";
            case String: return "String";
            case Type: return "Type";
        }

        throw std::logic_error("Invalid literal type");
    }
}
