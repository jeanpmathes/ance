#ifndef ANCE_BBT_TYPE_H
#define ANCE_BBT_TYPE_H

#include <ostream>

#include "ance/core/Identifier.h"
#include "ance/utility/Containers.h"

#include "Value.h"

namespace ance::bbt
{
    class TypeContext;

    /// Represents a type.
    class Type : public Value
    {
      public:
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        /// \param type_context The type context in which this type is created.
        Type(core::Identifier const& identifier, TypeContext& type_context);

        /// Creates a new type.
        /// \param identifier The identifier of the type.
        /// \param constructor_type The types used to construct this type.
        /// \param type_context The type context in which this type is created.
        Type(core::Identifier const& identifier, utility::List<utility::Shared<Type>> constructor_type, TypeContext& type_context);

        Type(Type const&)            = delete;
        Type& operator=(Type const&) = delete;

        Type(Type&&)            = delete;
        Type& operator=(Type&&) = delete;

        /// Gets the name of this type.
        [[nodiscard]] core::Identifier const& name() const;

        bool operator==(Type const& other) const;
        bool operator!=(Type const& other) const;

        // todo: add a function stripped() that removes all l-refs, e.g. &T -> T, &&T -> T, &&&T -> T, etc.

        [[nodiscard]] virtual bool isLReference() const;

        /// Gets the number of types used to construct this type.
        /// Note that member types (e.g. for structs) are not considered constructor types.
        [[nodiscard]] size_t getConstructorTypeCount() const;

        /// Gets the i-th constructor type of this type.
        [[nodiscard]] utility::Shared<Type> getConstructorType(size_t index);
        /// Gets the i-th constructor type of this type.
        [[nodiscard]] Type const& getConstructorType(size_t index) const;

        [[nodiscard]] std::string toString() const override;

      private:
        core::Identifier                     identifier_;
        utility::List<utility::Shared<Type>> constructor_types_;
    };

    /// Represents an assignable reference type.
    class LReferenceType : public Type
    {
      public:
        /// Creates a new l-value reference type.
        /// \param referenced_type The type being referenced.
        /// \param type_context The type context in which this type is created.
        LReferenceType(utility::Shared<Type> referenced_type, TypeContext& type_context);

        [[nodiscard]] bool isLReference() const override;

      private:
        utility::Shared<Type> referenced_type_;
    };

    /// Context providing access to all built-in types.
    class TypeContext
    {
      public:
        TypeContext();
        ~TypeContext();

        /// Get the boolean type, which has two values: true and false.
        utility::Shared<Type> getBool();

        /// Get the unit type, which has one value: ().
        utility::Shared<Type> getUnit();

        /// Get the size type, which has a platform-dependent size always larger enough to serve as a memory index.
        utility::Shared<Type> getSize();

        /// Get the string type.
        utility::Shared<Type> getString();

        /// Get the variable reference type, which is used to refer to variables.
        utility::Shared<Type> getVariableRef();// todo: should be split into variable type and reference type (not lref), variable type should be parameterized

        /// Get the untyped l-value reference type.
        /// \param referenced_type The type being referenced.
        utility::Shared<Type> getLRef(utility::Shared<Type> referenced_type);

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

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type);

#endif
