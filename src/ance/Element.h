#ifndef ANCE_SRC_ANCE_ELEMENT_H_
#define ANCE_SRC_ANCE_ELEMENT_H_

#include <vector>

#include "ance/ApplicationVisitor.h"
#include "ance/utility/Location.h"

namespace ance
{
    /**
     * The base class of all language elements.
     */
    class Element
    {
      public:
        /**
         * Get the source location of this element.
         * @return The source location.
         */
        [[nodiscard]] virtual ance::Location location() const = 0;

        /**
         * The accept method of the visitor pattern, the element will call the corresponding visit method.
         * @param visitor The visitor to accept.
         * @return The return value.
         */
        virtual bool accept(ance::ApplicationVisitor& visitor) = 0;

        /**
         * Add a child to this element. The children are ordered in the way they are added.
         * @param child The child to add.
         */
        void addChild(ance::Element& child);

        /**
         * Get the number of children of this element.
         * @return The child count.
         */
        size_t childCount();

        /**
         * Get the child with a given index.
         * @param index The index of the child to get.
         * @return The child with the given index.
         */
        ance::Element& getChild(size_t index);

      private:
        std::vector<std::reference_wrapper<ance::Element>> children_;
    };
}

#endif