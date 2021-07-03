#include "DictionaryElement.h"

#include "content_exception.h"

const data::Element& data::DictionaryElement::operator[](const std::string& key) const
{
	if (dict_.find(key) != dict_.end())
	{
		const std::unique_ptr<data::Element>& ptr = dict_.at(key);
		return *ptr;
	}
	else
	{
		throw data::content_exception("No element with key: " + key);
	}
}

void data::DictionaryElement::put(const std::string& key, std::unique_ptr<data::Element> element)
{
	dict_.insert({key, std::move(element)});
}
