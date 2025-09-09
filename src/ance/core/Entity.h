#ifndef ANCE_CORE_ENTITY_H
#define ANCE_CORE_ENTITY_H

#include <ostream>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Value.h"

namespace ance::core
{
    class Type;
    class Variable;

    /// Any named, resolvable entity in a scope, such as a variable or a function.
    class Entity
    {
      public:
        virtual ~Entity() = default;

        [[nodiscard]] virtual Identifier const& name() const = 0;
        // todo: a type() method - needs function types to be a thing

        virtual void* asFunction(); // todo: use actual function type
        [[nodiscard]] virtual void const* asFunction() const; // todo: use actual function type

        virtual Variable* asVariable();
        [[nodiscard]] virtual Variable const* asVariable() const;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Entity const& entity);

#endif
