#include "Element.h"

#include "content_exception.h"

const data::Element& data::Element::operator[](const std::string& key) const
{
	throw data::content_exception("No element with key: " + key);
}

std::vector<data::Element>::const_iterator data::Element::begin() const
{
	return empty_vector_.cend();
}

std::vector<data::Element>::const_iterator data::Element::end() const
{
	return empty_vector_.cend();
}

const std::string& data::Element::asString() const
{
	throw data::content_exception("Element is not of string type.");
}

bool data::Element::asBool() const
{
	throw data::content_exception("Element is not of bool type.");
}

