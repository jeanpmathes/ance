#ifndef ANCE_CORE_VARIABLE_H
#define ANCE_CORE_VARIABLE_H

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"

namespace ance::core
{
    /**
     * Represents a variable.
     */
    class Variable
    {
      public:
        /**
         * Creates a new variable.
         * @param identifier The identifier of the variable.
         * @param location The location where the variable was defined.
         */
        Variable(Identifier const& identifier, Location const& location);

        /**
         * Gets the identifier of this variable.
         */
        Identifier const& identifier() const;

        /**
         * Gets the location where this variable was defined.
         */
        Location const& location() const;

      private:
        Identifier identifier_;
        Location location_;
    };
}

#endif
