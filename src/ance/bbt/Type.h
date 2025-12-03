#ifndef ANCE_BBT_TYPE_H
#define ANCE_BBT_TYPE_H

#include <ostream>

#include "ance/core/Identifier.h"

#include "Value.h"

namespace ance::bbt
{
    /// Represents a type.
    class Type final : public Value
    {
    public:
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        explicit Type(core::Identifier const& identifier);

        Type(const Type&) = delete;
        Type& operator=(const Type&) = delete;

        Type(Type&&) = delete;
        Type& operator=(Type&&) = delete;

        /// Gets the name of this type.
        [[nodiscard]] core::Identifier const& name() const;

        /// Get the boolean type, which has two values: true and false.
        static utility::Shared<Type> Bool();

        /// Get the unit type, which has one value: ().
        static utility::Shared<Type> Unit();

        /// Get the size type, which has a platform-dependent size.
        static utility::Shared<Type> Size();

        /// Get the string type.
        static utility::Shared<Type> String();

        /// Get the variable reference type, which is used to refer to variables.
        static utility::Shared<Type> VariableRef(); // todo: should be split into variable type and reference type, variable type should be parameterized

        /// Get the untyped l-value reference type.
        static utility::Shared<Type> LRef(); // todo: should be parameterized, typed, and be &T rather than .T

        /// Get the identifier type, which is the type of all identifiers.
        static utility::Shared<Type> Ident();

        /// Get the function type.
        static utility::Shared<Type> Function(); // TODO: function type should be parameterized (signature and return type)

        /// Get the type-type - the type of all types.
        static utility::Shared<Type> Self();

        /// Get the scope type, which refers to scope values.
        static utility::Shared<Type> ScopeRef();

        /// Get the source location type.
        static utility::Shared<Type> Location();

        bool operator==(Type const& other) const;
        bool operator!=(Type const& other) const;

        // todo: add a function stripped() that removes all l-refs, e.g. &T -> T, &&T -> T, &&&T -> T, etc.

        /// Checks whether this type is assignable to another type.
        bool isAssignableTo(Type const& other) const; // todo: should also handle l-refs correctly

        [[nodiscard]] std::string            toString() const override;

      private:
        core::Identifier identifier_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type);

#endif
