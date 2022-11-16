#ifndef ANCE_SRC_MANAGEMENT_ELEMENTS_DICTIONARYELEMENT_H_
#define ANCE_SRC_MANAGEMENT_ELEMENTS_DICTIONARYELEMENT_H_

#include "Element.h"

#include <map>
#include <memory>

namespace data
{
    /**
     * Represents an element that contains a dictionary.
     */
    class DictionaryElement : public data::Element
    {
      public:
        std::optional<std::reference_wrapper<const data::Element>> operator[](std::string const& key) const override;

        /**
         * Add an element to the dictionary.
         * @param key The key of the element.
         * @param element The element.
         */
        void put(std::string const& key, std::unique_ptr<data::Element> element);

      private:
        std::map<std::string, std::unique_ptr<data::Element>> dict_;
    };
}

#endif
