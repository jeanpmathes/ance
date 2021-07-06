#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_DICTIONARYELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_DICTIONARYELEMENT_H_

#include "Element.h"

#include <map>
#include <memory>

namespace data
{
class DictionaryElement : public data::Element
{
	public:
		std::optional<std::reference_wrapper<const data::Element>> operator[] (const std::string& key) const override;
		void put(const std::string& key, std::unique_ptr<data::Element> element);

	private:
		std::map<std::string, std::unique_ptr<data::Element>> dict_;
};
}

#endif
