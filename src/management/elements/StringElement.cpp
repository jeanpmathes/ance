#include "StringElement.h"

data::StringElement::StringElement(const std::string& string) : string_(string)
{

}

const std::string& data::StringElement::asString() const
{
	return string_;
}
