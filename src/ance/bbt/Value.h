#ifndef ANCE_BBT_VALUE_H
#define ANCE_BBT_VALUE_H

#include <string>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"

namespace ance::bbt
{
    class Type;
    class TypeContext;

    /// Represents a value.
    class Value
    {
      protected:
        /// The concrete value class must supply its type, except when the type is "Type" when nullopt must be used to prevent infinite recursion.
        explicit Value(utility::Optional<utility::Shared<Type>> type, TypeContext& type_context);

      public:
        virtual ~Value() = default;

        utility::Shared<Type>             type();
        [[nodiscard]] Type const&         type() const;
        [[nodiscard]] virtual std::string toString() const = 0;

        template<typename T>
        bool is() const
        { return dynamic_cast<T const*>(this) != nullptr; }

        template<typename T>
        T const& as() const
        {
            T const* casted = dynamic_cast<T const*>(this);
            if (casted == nullptr) throw std::bad_cast();
            return *casted;
        }

      private:
        utility::Optional<utility::Shared<Type>> type_;
        TypeContext&                             type_context_;
    };

    class Unit final : public Value
    {
      public:
        explicit Unit(TypeContext& type_context);

        static utility::Shared<Unit> make(TypeContext& type_context);

        ~Unit() override = default;

        [[nodiscard]] std::string toString() const override;
    };

    class Bool final : public Value
    {
      public:
        Bool(bool value, TypeContext& type_context);

        static utility::Shared<Bool> make(bool value, TypeContext& type_context);

        ~Bool() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] bool value() const;

      private:
        bool value_;
    };

    class Size final : public Value
    {
      public:
        Size(size_t value, TypeContext& type_context);

        static utility::Shared<Size> make(size_t value, TypeContext& type_context);

        ~Size() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] size_t value() const;

      private:
        size_t value_;
    };

    class Identifier final : public Value// todo: try to make the core::Identifier a value in some way
    {
      public:
        Identifier(core::Identifier const& identifier, TypeContext& type_context);

        static utility::Shared<Identifier> make(core::Identifier const& identifier, TypeContext& type_context);

        ~Identifier() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] core::Identifier const& value() const;

      private:
        core::Identifier identifier_;
    };

    class Location final : public Value
    {
      public:
        explicit Location(core::Location const& location, TypeContext& type_context);

        static utility::Shared<Location> make(core::Location const& location, TypeContext& type_context);

        ~Location() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] core::Location const& value() const;

      private:
        core::Location location_;
    };

    class String final : public Value
    {
      public:
        String(std::string value, TypeContext& type_context);

        static utility::Shared<String> make(std::string value, TypeContext& type_context);

        ~String() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] std::string const& value() const;

      private:
        std::string value_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value);

#endif
