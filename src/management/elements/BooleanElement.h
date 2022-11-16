#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_BOOLEANELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_BOOLEANELEMENT_H_

#include "Element.h"

#include <memory>

namespace data
{
    /**
     * Represents an element that contains a boolean value.
     */
    class BooleanElement : public data::Element
    {
      public:
        /**
         * Create an element.
         * @param b The boolean value.
         */
        explicit BooleanElement(bool b);

        [[nodiscard]] std::optional<bool> asBool() const override;

      private:
        bool b_;
    };
}

#endif
