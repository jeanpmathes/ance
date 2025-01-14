#include <cassert>

#include "lang/Assigner.h"
#include "lang/utility/Storage.h"

lang::Assigner::operator Value() const
{
    return value_;
}

bool lang::Assigner::isFinal() const
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}

bool lang::Assigner::hasSymbol() const
{
    return value_ != REFERENCE_BINDING && value_ != UNSPECIFIED;
}

std::string lang::Assigner::getSymbol() const
{
    assert(hasSymbol());

    switch (value_)
    {
        case COPY_ASSIGNMENT:
            return "<:";
        case MOVE_ASSIGNMENT:
            return "<-";
        case FINAL_COPY_ASSIGNMENT:
            return ":=";

        default:
            return "";
    }
}

void lang::Assigner::synchronize(lang::Assigner* assigner, Storage& storage)
{
    uint8_t value = assigner->value_;
    storage.sync(value);
    assigner->value_ = static_cast<Value>(value);
}
