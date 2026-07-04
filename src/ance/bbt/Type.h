#ifndef ANCE_BBT_TYPE_H
#define ANCE_BBT_TYPE_H

#include <ostream>

#include "ance/core/BinaryOperator.h"
#include "ance/core/Identifier.h"
#include "ance/core/UnaryOperator.h"
#include "ance/core/VariabilityModifier.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Optional.h"

#include "Value.h"

namespace ance::cet
{
    class Runner;
}

namespace ance::bbt
{
    class TypeContext;

    /// Represents a type.
    /// A type is a value of itself as the type, and each value has a type.
    /// Types are not compared based on identity but by value.
    class Type : public virtual Value
    {
      public:
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        Type(core::Identifier const& identifier);

        /// Creates a new numeric type with binary operator functions.
        /// \param identifier The identifier of the type.
        /// \param constructing_types The types used to construct this type.
        Type(core::Identifier const& identifier, utility::List<utility::Shared<Type const>> constructing_types);

        Type(Type const&)            = delete;
        Type& operator=(Type const&) = delete;

        Type(Type&&)            = delete;
        Type& operator=(Type&&) = delete;

        ~Type() override = default;

        /// Gets the name of this type.
        [[nodiscard]] core::Identifier const& name() const;

        /// Gets the annotated name of this type, for compiler messages.
        [[nodiscard]] std::string annotated() const;

        // todo: add a function stripped() that removes all refs, e.g. &T -> T, &&T -> T, &&&T -> T, etc.

        [[nodiscard]] virtual bool isReference() const;
        [[nodiscard]] virtual bool isArray() const;

        /// The variability of this type.
        [[nodiscard]] virtual core::VariabilityModifier variability() const;

        /// Gets the number of types used to construct this type.
        /// Note that member types (e.g., for structs) are not considered constructing types.
        [[nodiscard]] size_t getConstructingTypeCount() const;

        /// Gets the i-th constructing type of this type.
        [[nodiscard]] utility::Shared<Type const> getConstructingType(size_t index) const;

        [[nodiscard]] std::string toString() const override;

        /// Returns true if this type has a unary operator function for the given operator.
        [[nodiscard]] bool isUnaryOperatorDefined(core::UnaryOperator unary_operator) const;

        /// Returns the identifier of the unary operator function for the given operator, if defined.
        [[nodiscard]] utility::Optional<core::Identifier> getUnaryOperatorFunctionIdentifier(
            core::UnaryOperator unary_operator)
            const;// todo: when reworking how ops are defined, this should be removed because retrieval would ideally not be name based

        /// Returns true if this type has a binary operator function for the given operator and right-hand type.
        [[nodiscard]] bool isBinaryOperatorDefined(core::BinaryOperator binary_operator, Type const& rhs_type) const;

        /// Returns the binary operator function for the given operator and right-hand type, if defined.
        [[nodiscard]] utility::Optional<core::Identifier> getBinaryOperatorFunctionIdentifier(
            core::BinaryOperator binary_operator,
            Type const& rhs_type) const;// todo: when reworking how ops are defined, this should be removed because retrieval would ideally not be name based

        /// Returns true if this type supports subscript access.
        /// If this is overridden and returns true, the corresponding value class needs to provide an implementation for \c access .
        [[nodiscard]] virtual bool isSubscriptDefined() const;

        /// Returns the element type accessed by the subscript operation.
        /// Only valid to call if \c isSubscriptDefined returns true.
        [[nodiscard]] virtual utility::Shared<Type const> getSubscriptType() const;

        /// Returns true if a given subscript index is within bounds.
        /// Only valid to call if \c isSubscriptDefined returns true.
        [[nodiscard]] virtual bool isSubscriptInBounds(size_t index) const;

      private:
        friend class TypeContext;

        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };

    /// Used to represent any basic type.
    class BasicType
        : public virtual ValueBase<BasicType>
        , public Type
    {
      public:
        /// Creates a new basic type.
        /// \param identifier The identifier of this type. It is also used to determine equality.
        /// \param type_context The type context in which this type is created.
        BasicType(core::Identifier const& identifier, TypeContext& type_context);

        using Value::equals;

        [[nodiscard]] bool equals(BasicType const& other) const override;
    };

    /// Represents a reference type.
    class ReferenceType
        : public virtual ValueBase<ReferenceType>
        , public Type// todo: think about this type vs. reference wrapper, maybe this should have reference-wrapper like behavior
    {
      public:
        /// Creates a new reference type.
        /// \param referenced_type The type being referenced.
        /// \param variability The variability of the reference.
        /// \param type_context The type context in which this type is created.
        ReferenceType(utility::Shared<Type const> referenced_type, core::VariabilityModifier variability, TypeContext& type_context);

        [[nodiscard]] bool isReference() const override;

        /// The variability of this type.
        [[nodiscard]] core::VariabilityModifier variability() const override;

        using Value::equals;

        [[nodiscard]] bool equals(ReferenceType const& other) const override;

      private:
        utility::Shared<Type const> referenced_type_;
        core::VariabilityModifier variability_;
    };

    /// Represents a fixed-size array type.
    class ArrayType
        : public virtual ValueBase<ArrayType>, public Type
    {
      public:
        /// Creates a new array type.
        /// \param element_type The type of each array element.
        /// \param length The number of elements in the array.
        /// \param type_context The type context in which this type is created.
        ArrayType(utility::Shared<Type const> element_type, size_t length, TypeContext& type_context);

        [[nodiscard]] bool                  isArray() const override;
        [[nodiscard]] utility::Shared<Type const> elementType() const;
        [[nodiscard]] size_t                length() const;

        [[nodiscard]] bool                  isSubscriptDefined() const override;
        [[nodiscard]] utility::Shared<Type const> getSubscriptType() const override;
        [[nodiscard]] bool                  isSubscriptInBounds(size_t index) const override;

        using Value::equals;

        [[nodiscard]] bool equals(ArrayType const& other) const override;

      private:
        utility::Shared<Type const> element_type_;
        size_t length_;
    };

    /// Context providing access to all built-in types.
    /// Note that this constructs new values, but because type comparison is not identity- but value-based, this is not an issue.
    class TypeContext
    {
      public:
        explicit TypeContext(cet::Runner& runner);
        ~TypeContext();

        using T = Type;

        /// Get the boolean type, which has two values: true and false.
        utility::Shared<const T> Bool();

        /// Get the unit type, which has one value: ().
        utility::Shared<const T> Unit();

        /// Get the size type, which has a platform-dependent size always larger enough to serve as a memory index.
        utility::Shared<const T> Size();

        /// Get a float type by its precision.
        utility::Shared<const T> Float(core::Precision precision);

        /// Get the string type.
        utility::Shared<const T> String();

        /// Get the variable reference type, which is used to refer to variables.
        // todo: should be split into variable type and reference type (not the current ref), variable type should be parameterized
        utility::Shared<const T> VariableRef();

        /// Get a reference type.
        /// \param referenced_type The type being referenced.
        /// \param variability The variability of the referenced value.
        utility::Shared<const T> Reference(utility::Shared<const T> referenced_type, core::VariabilityModifier variability);

        /// Get a fixed-size array type.
        /// \param element_type The type of each array element.
        /// \param length The number of elements in the array.
        utility::Shared<const T> Array(utility::Shared<const T> element_type, size_t length);

        /// Get the identifier type, which is the type of all identifiers.
        utility::Shared<const T> Identifier();

        /// Get the function type.
        utility::Shared<const T> Function();// TODO: function type should be parameterized (signature and return type)

        /// Get the type-type - the type of all types.
        utility::Shared<const T> Type();

        /// Get the type-type - the type of all types.
        [[nodiscard]] utility::Shared<const T> Type() const;

        /// Get the scope type, which refers to scope values.
        utility::Shared<const T> ScopeRef();

        /// Get the source location type.
        utility::Shared<const T> Location();

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;

        utility::Shared<const T> type_type_;
    };
}

#endif
