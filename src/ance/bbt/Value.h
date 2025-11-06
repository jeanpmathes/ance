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

    class UnitValue final : public Value
    {
    public:
        UnitValue();

        static utility::Shared<UnitValue> make();

        ~UnitValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;
    };

    class BoolValue final : public Value
    {
    public:
        explicit BoolValue(bool value);

        static utility::Shared<BoolValue> make(bool value);

        ~BoolValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] bool value() const;

    private:
        bool value_;
    };

    class SizeValue final : public Value
    {
    public:
        explicit SizeValue(size_t value);

        static utility::Shared<SizeValue> make(size_t value);

        ~SizeValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] size_t value() const;

    private:
        size_t value_;
    };

    class EntityRefValue final : public Value
    {
    public:
        explicit EntityRefValue(core::Entity const& entity);

        static utility::Shared<EntityRefValue> make(core::Entity const& entity);

        ~EntityRefValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Entity const& value() const;

    private:
        core::Entity const& entity_;
    };

    class IdentifierValue final : public Value
    {
    public:
        explicit IdentifierValue(core::Identifier const& identifier);

        static utility::Shared<IdentifierValue> make(core::Identifier const& identifier);

        ~IdentifierValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Identifier const& value() const;

    private:
        core::Identifier identifier_;
    };

    class TypeValue final : public Value
    {
    public:
        explicit TypeValue(core::Type const& type);

        static utility::Shared<TypeValue> make(core::Type const& type);

        ~TypeValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Type const& value() const;

    private:
        core::Type const& type_;
    };

    class LocationValue final : public Value
    {
    public:
        explicit LocationValue(core::Location const& location);

        static utility::Shared<LocationValue> make(core::Location const& location);

        ~LocationValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] core::Location const& value() const;

    private:
        core::Location location_;
    };

    class StringValue final : public Value
    {
    public:
        explicit StringValue(std::string value);

        static utility::Shared<StringValue> make(std::string value);

        ~StringValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] std::string const& value() const;
    private:
        std::string value_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value);

#endif
