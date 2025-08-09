#ifndef ANCE_CORE_VARIABLE_H
#define ANCE_CORE_VARIABLE_H

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"
#include "ance/core/Entity.h"

namespace ance::core
{
    class Type;

    /// Represents a variable.
    class Variable final : public Entity
    {
      public:
        /// Creates a new variable.
        /// \param identifier The identifier of the variable.
        /// \param type The type of the variable.
        /// \param location The location where the variable was defined.
        Variable(Identifier const& identifier, Type const& type, Location const& location);

        ~Variable() override = default;

        /// Gets the identifier of this variable.
        [[nodiscard]] Identifier const& name() const override;

        /// Gets the type of this variable.
        [[nodiscard]] Type const& type() const;

        /// Gets the location where this variable was defined.
        [[nodiscard]] Location const& location() const;

        Variable*                       asVariable() override;
        [[nodiscard]] Variable const* asVariable() const override;

      private:
        Identifier  identifier_;
        Type const& type_;
        Location    location_;
    };
}

#endif
