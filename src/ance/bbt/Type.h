#ifndef ANCE_BBT_TYPE_H
#define ANCE_BBT_TYPE_H

#include <ostream>

#include "ance/core/Identifier.h"

#include "Value.h"

namespace ance::bbt
{
    class TypeContext;

    /// Represents a type.
    class Type final : public Value
    {
      public:
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        explicit Type(core::Identifier const& identifier, TypeContext& type_context);

        Type(Type const&)            = delete;
        Type& operator=(Type const&) = delete;

        Type(Type&&)            = delete;
        Type& operator=(Type&&) = delete;

        /// Gets the name of this type.
        [[nodiscard]] core::Identifier const& name() const;

        bool operator==(Type const& other) const;
        bool operator!=(Type const& other) const;

        // todo: add a function stripped() that removes all l-refs, e.g. &T -> T, &&T -> T, &&&T -> T, etc.

        /// Checks whether this type is assignable to another type.
        [[nodiscard]] bool isAssignableTo(Type const& other) const;// todo: should also handle l-refs correctly

        [[nodiscard]] std::string toString() const override;

      private:
        core::Identifier identifier_;
    };

    /// Context providing access to all built-in types.
    class TypeContext
    {
      public:
        /// Get the boolean type, which has two values: true and false.
        utility::Shared<Type> getBool();

        /// Get the unit type, which has one value: ().
        utility::Shared<Type> getUnit();

        /// Get the size type, which has a platform-dependent size always larger enough to serve as a memory index.
        utility::Shared<Type> getSize();

        /// Get the string type.
        utility::Shared<Type> getString();

        /// Get the variable reference type, which is used to refer to variables.
        utility::Shared<Type> getVariableRef();// todo: should be split into variable type and reference type, variable type should be parameterized

        /// Get the untyped l-value reference type.
        utility::Shared<Type> getLRef();// todo: should be parameterized, typed, and be &T rather than .T

        /// Get the identifier type, which is the type of all identifiers.
        utility::Shared<Type> getIdentifier();

        /// Get the function type.
        utility::Shared<Type> getFunction();// TODO: function type should be parameterized (signature and return type)

        /// Get the type-type - the type of all types.
        utility::Shared<Type> getType();

        /// Get the scope type, which refers to scope values.
        utility::Shared<Type> getScopeRef();

        /// Get the source location type.
        utility::Shared<Type> getLocation();
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type);

#endif
