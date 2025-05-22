#ifndef ANCE_CORE_VARIABLE_H
#define ANCE_CORE_VARIABLE_H

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"

namespace ance::core
{
    class Type;

    /// Represents a variable.
    class Variable
    {
      public:
        /// Creates a new variable.
        /// \param identifier The identifier of the variable.
        /// \param type The type of the variable.
        /// \param location The location where the variable was defined.
        Variable(Identifier const& identifier, Type const& type, Location const& location);

        /// Gets the identifier of this variable.
        [[nodiscard]] Identifier const& identifier() const;

        /// Gets the type of this variable.
        [[nodiscard]] Type const& type() const;

        /// Gets the location where this variable was defined.
        [[nodiscard]] Location const& location() const;

      private:
        Identifier  identifier_;
        Type const& type_;
        Location    location_;
    };
}

#endif
