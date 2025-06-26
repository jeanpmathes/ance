#ifndef ANCE_CORE_VALUE_H
#define ANCE_CORE_VALUE_H

#include <string>

#include "ance/utility/Owners.h"
#include "ance/core/Type.h"

namespace ance::core
{
    class Type;

    union Storage
    {
        bool boolean;
        size_t size;
        TypeID type_id;
    };

    /// Represents a value.
    class Value // todo: use inheritance-based value class instead of the current switching one (see old code)
    {
    public:
        /// Creates a new value.
        Value(Type const& type, Storage storage);

        /// Create a boolean value.
        static utility::Shared<Value> makeBool(bool value);

        /// Create a unit value.
        static utility::Shared<Value> makeUnit();

        /// Create a size value.
        static utility::Shared<Value> makeSize(size_t value);

        /// Create a type value.
        static utility::Shared<Value> makeType(Type const& type);

        /// Create a default value of the given type.
        static utility::Shared<Value> makeDefault(Type const& type);

        [[nodiscard]] Type const& type() const;
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] bool getBool() const;
        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] Type const& getType() const;

        [[nodiscard]] utility::Shared<Value> clone() const;

      private:
        Type const& type_;
        Storage storage_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Value const& value);

#endif
