#ifndef ANCE_BBT_VALUE_H
#define ANCE_BBT_VALUE_H

#include <string>

#include "ance/utility/Owners.h"
#include "ance/core/Type.h"
#include "ance/core/Location.h"

namespace ance::core
{
    class Type;
    class Entity;
}

namespace ance::bbt
{
    /// Represents a value.
    class Value
    {
    protected:
        explicit Value(core::Type const& type);

    public:
        virtual ~Value() = default;

        [[nodiscard]] core::Type const& type() const;
        [[nodiscard]] virtual std::string toString() const = 0;

        [[nodiscard]] virtual utility::Shared<Value> clone() const = 0;

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
        core::Type const& type_;
    };

    class Unit final : public Value
    {
    public:
        Unit();

        static utility::Shared<Unit> make();

        ~Unit() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;
    };

    class Bool final : public Value
    {
    public:
        explicit Bool(bool value);

        static utility::Shared<Bool> make(bool value);

        ~Bool() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

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
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] size_t value() const;

    private:
        size_t value_;
    };

    class Identifier final : public Value
    {
    public:
        explicit Identifier(core::Identifier const& identifier);

        static utility::Shared<Identifier> make(core::Identifier const& identifier);

        ~Identifier() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Identifier const& value() const;

    private:
        core::Identifier identifier_;
    };

    class Type final : public Value
    {
    public:
        explicit Type(core::Type const& type);

        static utility::Shared<Type> make(core::Type const& type);

        ~Type() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Type const& value() const;

    private:
        core::Type const& type_;
    };

    class Location final : public Value
    {
    public:
        explicit Location(core::Location const& location);

        static utility::Shared<Location> make(core::Location const& location);

        ~Location() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

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
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] std::string const& value() const;
    private:
        std::string value_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value);

#endif
