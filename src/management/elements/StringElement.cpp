#include "StringElement.h"

#include <utility>

data::StringElement::StringElement(std::string string) : string_(std::move(string))
{

}

const std::string& data::StringElement::asString() const
{
	return string_;
}
