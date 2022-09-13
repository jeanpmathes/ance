#ifndef ANCE_SRC_LANG_ELEMENT_H_
#define ANCE_SRC_LANG_ELEMENT_H_

#include <vector>

#include "lang/Visitor.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
}

namespace lang
{
    /**
     * The base class of all language elements.
     * @tparam Derived The derived class.
     * @tparam TList The list of all types that can be visited, use the macro.
     */
    template<typename Derived, typename... TList>
    class Element : public virtual lang::Visitable<TList...>
    {
      public:
        /**
         * The accept method of the visitor pattern, the element will call the corresponding visit method.
         * @param visitor The visitor to accept.
         * @return The return value.
         */
        std::any accept(Visitor<TList...>& visitor) override { return visitor.visit(static_cast<Derived&>(*this)); }
    };
}

#endif

