#include "ListElement.h"

std::vector<data::Element>::const_iterator data::ListElement::begin() const
{
	return list_.cbegin();
}

std::vector<data::Element>::const_iterator data::ListElement::end() const
{
	return list_.cend();
}

void data::ListElement::put(std::unique_ptr<data::Element> element)
{
	data::Element& e = *element.release();
	list_.push_back(std::move(e));
}


