#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_STRINGELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_STRINGELEMENT_H_

#include "Element.h"

#include <memory>

namespace data
{
    /**
     * Represents an element containing a string.
     */
    class StringElement : public data::Element
    {
      public:
        /**
         * Create a new string element.
         * @param string The string value.
         */
        explicit StringElement(std::string string);

        [[nodiscard]] std::optional<std::reference_wrapper<const std::string>> asString() const override;

      private:
        std::string string_;
    };
}

#endif
