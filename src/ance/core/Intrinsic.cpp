#include "Intrinsic.h"

#include <map>
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
            return "b_2_str";
        case LOG:
            return "log";
        case INCLUDE:
            return "include";
        case CALL_INTRINSIC:
            return "call_intrinsic";
    }
}

std::optional<ance::core::Intrinsic> ance::core::Intrinsic::fromString(std::string const& name)
{
    static std::map<std::string, Value> const lookup = {
        {"nop", NO_OPERATION},
        {"declare", DECLARE},
        {"resolve", RESOLVE},
        {"get_parent", GET_PARENT},
        {"b_2_str", B_2_STR},
        {"log", LOG},
        {"include", INCLUDE},
        {"call_intrinsic", CALL_INTRINSIC},
    };

    auto const it = lookup.find(name);
    if (it == lookup.end()) return std::nullopt;

    return Intrinsic(it->second);
}
