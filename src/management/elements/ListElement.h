#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_LISTELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_LISTELEMENT_H_

#include "Element.h"

#include <memory>
#include <vector>

namespace data
{
class ListElement : public data::Element
{
	public:
		[[nodiscard]] std::vector<std::reference_wrapper<const data::Element>>::const_iterator begin() const override;

		[[nodiscard]] std::vector<std::reference_wrapper<const data::Element>>::const_iterator end() const override;

		void put(std::unique_ptr<data::Element> element);

	private:
		std::vector<std::reference_wrapper<const data::Element>> const_list_;
		std::vector<std::unique_ptr<Element>> list_;
};
}

#endif
