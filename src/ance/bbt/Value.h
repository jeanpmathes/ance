#ifndef ANCE_BBT_VALUE_H
#define ANCE_BBT_VALUE_H

#include <string>

#include "ance/utility/Owners.h"

#include "ance/core/Location.h"
#include "ance/core/Identifier.h"

namespace ance::bbt
{
    class Type;

    /// Represents a value.
    class Value
    {
    protected:
        /// The concrete value class must supply its type, except when the type is "Type" when nullopt must be used to prevent infinite recursion.
        explicit Value(utility::Optional<utility::Shared<Type>> type);

    public:
        virtual ~Value() = default;

        utility::Shared<Type> type();
        [[nodiscard]] Type const& type() const;
        [[nodiscard]] virtual std::string toString() const = 0;

        template<typename T>
        bool is() const
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
        utility::Optional<utility::Shared<Type>> type_;
    };

    class Unit final : public Value
    {
    public:
        Unit();

        static utility::Shared<Unit> make();

        ~Unit() override = default;

        [[nodiscard]] std::string            toString() const override;
    };

    class Bool final : public Value
    {
    public:
        explicit Bool(bool value);

        static utility::Shared<Bool> make(bool value);

        ~Bool() override = default;

        [[nodiscard]] std::string            toString() const override;

        [[nodiscard]] bool value() const;

    private:
        bool value_;
    };

    class Size final : public Value
    {
    public:
        explicit Size(size_t value);

        static utility::Shared<Size> make(size_t value);

        ~Size() override = default;

        [[nodiscard]] std::string            toString() const override;

        [[nodiscard]] size_t value() const;

    private:
        size_t value_;
    };

    class Identifier final : public Value // todo: try to make the core::Identifier a value in some way
    {
    public:
        explicit Identifier(core::Identifier const& identifier);

        static utility::Shared<Identifier> make(core::Identifier const& identifier);

        ~Identifier() override = default;

        [[nodiscard]] std::string            toString() const override;

        [[nodiscard]] core::Identifier const& value() const;

    private:
        core::Identifier identifier_;
    };

    class Location final : public Value
    {
    public:
        explicit Location(core::Location const& location);

        static utility::Shared<Location> make(core::Location const& location);

        ~Location() override = default;

        [[nodiscard]] std::string            toString() const override;

        [[nodiscard]] core::Location const& value() const;

    private:
        core::Location location_;
    };

    class String final : public Value
    {
    public:
        explicit String(std::string value);

        static utility::Shared<String> make(std::string value);

        ~String() override = default;

        [[nodiscard]] std::string            toString() const override;

        [[nodiscard]] std::string const& value() const;
    private:
        std::string value_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value);

#endif
