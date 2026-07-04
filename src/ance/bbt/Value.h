#ifndef ANCE_BBT_VALUE_H
#define ANCE_BBT_VALUE_H

#include <span>
#include <string>

#include <llvm/ADT/APFloat.h>

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"
#include "ance/core/Precision.h"

namespace ance::bbt
{
    class Type;
    class TypeContext;

    /// Represents a value. This class is immutable and all of its implementations must be immutable as well.
    class Value
    {
      protected:
        /// The concrete value class must supply its type, except when the type is "Type"; then \c nullopt must be used to prevent infinite recursion.
        explicit Value(utility::Optional<utility::Shared<Type const>> type, TypeContext& type_context);

      public:
        virtual ~Value() = default;

        [[nodiscard]] utility::Shared<Type const> type() const;
        [[nodiscard]] virtual std::string         toString() const = 0;

        /// \brief Access this value using an index.
        /// Access can either be performed in load or replace mode.
        /// Invalid access is allowed and simply returns \c std::nullopt .
        /// \param index The index of the element to access.
        /// \param replacement If this is null, the value at the index is loaded and returned. If this is not null, a copy of this value is returned with the indexed element replaced. If passed, it must be of a valid type.
        /// \param type_context The type context.
        /// \return Depending on the mode, either the loaded element or the modified copy. If the access is out of bounds or not supported at all, \c std::nullopt is returned.
        [[nodiscard]] virtual utility::Optional<utility::Shared<Value const>> access(size_t                        index,
                                                                                     utility::Shared<Value const>* replacement,
                                                                                     TypeContext&                  type_context) const;

        /// Checks whether this value is equal to another value.
        [[nodiscard]] virtual bool equals(Value const& other) const = 0;

        [[nodiscard]] bool operator==(Value const& other) const;
        [[nodiscard]] bool operator!=(Value const& other) const;

        template<typename T>
        [[nodiscard]] bool is() const
        {
            return dynamic_cast<T const*>(this) != nullptr;
        }

        template<typename T>
        T const& as() const
        {
            T const* casted = dynamic_cast<T const*>(this);
            if (casted == nullptr) throw std::bad_cast();
            return *casted;
        }

      private:
        utility::Optional<utility::Shared<Type const>> type_;
        TypeContext&                                   type_context_;
    };

    template<typename T>
    class ValueBase : public virtual Value
    {
      public:
        ~ValueBase() override = default;

        // ReSharper disable once CppEnforceOverridingFunctionStyle
        [[nodiscard]] virtual bool equals(T const& other) const = 0;

        [[nodiscard]] bool equals(Value const& other) const final
        {
            if (other.is<T>())
            {
                return equals(other.as<T>());
            }

            return false;
        }
    };

    class Unit final : public ValueBase<Unit>
    {
      public:
        explicit Unit(TypeContext& type_context);

        static utility::Shared<Unit> make(TypeContext& type_context);

        ~Unit() override = default;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] bool        equals(Unit const& other) const override;
    };

    class Bool final : public ValueBase<Bool>
    {
      public:
        Bool(bool value, TypeContext& type_context);

        static utility::Shared<Bool> make(bool value, TypeContext& type_context);

        ~Bool() override = default;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] bool        value() const;
        [[nodiscard]] bool        equals(Bool const& other) const override;

      private:
        bool value_;
    };

    class Size final : public ValueBase<Size>
    {
      public:
        Size(size_t value, TypeContext& type_context);

        static utility::Shared<Size> make(size_t value, TypeContext& type_context);
        static utility::Shared<Size> make(std::string const& value, TypeContext& type_context);

        ~Size() override = default;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] size_t      value() const;
        [[nodiscard]] bool        equals(Size const& other) const override;

      private:
        size_t value_;
    };

    class Float final : public ValueBase<Float>
    {
      public:
        Float(llvm::APFloat value, TypeContext& type_context);

        static utility::Shared<Float> make(llvm::APFloat value, TypeContext& type_context);
        static utility::Shared<Float> make(std::string const& value, core::Precision precision, TypeContext& type_context);

        ~Float() override = default;

        [[nodiscard]] std::string   toString() const override;
        [[nodiscard]] llvm::APFloat value() const;
        [[nodiscard]] bool          equals(Float const& other) const override;

      private:
        llvm::APFloat value_;
    };

    class Identifier final : public ValueBase<Identifier>// todo: try to make the core::Identifier a value in some way
    {
      public:
        Identifier(core::Identifier const& identifier, TypeContext& type_context);

        static utility::Shared<Identifier> make(core::Identifier const& identifier, TypeContext& type_context);

        ~Identifier() override = default;

        [[nodiscard]] std::string             toString() const override;
        [[nodiscard]] core::Identifier const& value() const;
        [[nodiscard]] bool                    equals(Identifier const& other) const override;

      private:
        core::Identifier identifier_;
    };

    class Location final : public ValueBase<Location>
    {
      public:
        explicit Location(core::Location const& location, TypeContext& type_context);

        static utility::Shared<Location> make(core::Location const& location, TypeContext& type_context);

        ~Location() override = default;

        [[nodiscard]] std::string           toString() const override;
        [[nodiscard]] core::Location const& value() const;
        [[nodiscard]] bool                  equals(Location const& other) const override;

      private:
        core::Location location_;
    };

    class String final : public ValueBase<String>
    {
      public:
        String(std::string value, TypeContext& type_context);

        static utility::Shared<String> make(std::string value, TypeContext& type_context);

        ~String() override = default;

        [[nodiscard]] std::string        toString() const override;
        [[nodiscard]] std::string const& value() const;
        [[nodiscard]] bool               equals(String const& other) const override;

      private:
        std::string value_;
    };

    class Array final : public ValueBase<Array>
    {
      public:
        Array(utility::Shared<Type const> array_type, utility::List<utility::Shared<Value const>> element_list, TypeContext& type_context);

        static utility::Shared<Array> make(utility::Shared<Type const>                 array_type,
                                           utility::List<utility::Shared<Value const>> element_list,
                                           TypeContext&                                type_context);

        ~Array() override = default;

        [[nodiscard]] std::string                                     toString() const override;
        [[nodiscard]] utility::Optional<utility::Shared<Value const>> access(size_t                        index,
                                                                             utility::Shared<Value const>* replacement,
                                                                             TypeContext&                  type_context) const override;
        [[nodiscard]] std::span<utility::Shared<Value const> const>   elements() const;
        [[nodiscard]] bool                                            equals(Array const& other) const override;

        [[nodiscard]] bool   isEmpty() const;
        [[nodiscard]] size_t length() const;

      private:
        utility::List<utility::Shared<Value const>> elements_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value);

#endif
