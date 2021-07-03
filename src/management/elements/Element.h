#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_

#include <string>
#include <vector>

namespace data
{
class Element
{
	public:
		virtual const Element& operator[] (const std::string& key) const;

		[[nodiscard]] virtual std::vector<const data::Element*>::const_iterator begin() const;

		[[nodiscard]] virtual std::vector<const data::Element*>::const_iterator end() const;

		[[nodiscard]] virtual const std::string& asString() const;

		[[nodiscard]] virtual bool asBool() const;

		virtual ~Element() = 0;

	private:
		inline static std::vector<const data::Element*> empty_vector_;
};
}

#endif
