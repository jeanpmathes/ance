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

		[[nodiscard]] virtual std::vector<Element>::const_iterator begin() const;

		[[nodiscard]] virtual std::vector<Element>::const_iterator end() const;

		[[nodiscard]] virtual const std::string& asString() const;

		[[nodiscard]] virtual bool asBool() const;

		virtual ~Element() = default;

	private:
		inline static std::vector<Element> empty_vector_;
};
}

#endif
