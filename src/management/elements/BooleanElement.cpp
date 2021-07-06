#include "BooleanElement.h"

data::BooleanElement::BooleanElement(bool b) : b_(b)
{

}

std::optional<bool> data::BooleanElement::asBool() const
{
	return b_;
}
