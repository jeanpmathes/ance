#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_STRINGELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_STRINGELEMENT_H_

#include "Element.h"

#include <memory>

namespace data
{
class StringElement : public data::Element
{
	public:
		explicit StringElement(const std::string& string);
		[[nodiscard]] const std::string & asString() const override;

	private:
		const std::string& string_;
};
}

#endif
