#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_BOOLEANELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_BOOLEANELEMENT_H_

#include "Element.h"

#include <memory>

namespace data
{
class BooleanElement : public data::Element
{
	public:
		explicit BooleanElement(bool b);
		[[nodiscard]] std::optional<bool> asBool() const override;

	private:
		bool b_;
};
}

#endif
