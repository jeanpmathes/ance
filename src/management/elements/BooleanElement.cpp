#include "BooleanElement.h"

data::BooleanElement::BooleanElement(bool b) : b_(b) {}

Optional<bool> data::BooleanElement::asBool() const
{
    return b_;
}
