#ifndef ANCE_SRC_LANG_LOCATED_H_
#define ANCE_SRC_LANG_LOCATED_H_

#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
}

namespace lang
{
    /**
     * Base class for elements in the AST that have a location and scope.
     */
    class Located
    {
      public:
        virtual ~Located() = default;

        /**
         * Get the containing scope.
         */
        [[nodiscard]] virtual lang::Scope& scope() = 0;

        /**
         * Get the containing scope.
         */
        [[nodiscard]] virtual lang::Scope const& scope() const = 0;

        /**
         * Get the source location of this statement.
         */
        [[nodiscard]] virtual lang::Location location() const = 0;
    };
}

#endif
