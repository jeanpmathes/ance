#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_ELEMENT_H_

#include <optional>
#include <string>
#include <vector>

namespace data
{
    /**
     * Base class of data file elements.
     */
    class Element
    {
      public:
        /**
         * Access an element by key.
         * @param key The key.
         * @return An optional element.
         */
        virtual std::optional<std::reference_wrapper<const data::Element>> operator[](std::string const& key) const;

        [[nodiscard]] virtual std::vector<std::reference_wrapper<const data::Element>>::const_iterator begin() const;

        [[nodiscard]] virtual std::vector<std::reference_wrapper<const data::Element>>::const_iterator end() const;

        /**
         * Get the value of this element as string.
         * @return An optional string, only filled if this element is actually a string.
         */
        [[nodiscard]] virtual std::optional<std::reference_wrapper<const std::string>> asString() const;

        /**
         * Get the value of this element as bool.
         * @return An optional bool, only filled if this element is actually a bool.
         */
        [[nodiscard]] virtual std::optional<bool> asBool() const;

        virtual ~Element() = 0;

      private:
        inline static std::vector<std::reference_wrapper<const data::Element>> empty_vector_;
    };
}

#endif
