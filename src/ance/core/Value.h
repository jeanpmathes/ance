#ifndef ANCE_CORE_VALUE_H
#define ANCE_CORE_VALUE_H

#include <string>

#include "ance/utility/Owners.h"

namespace ance::core
{
    class Type;

    /// Represents a value.
    class Value // todo: use inheritance-based value class instead of the current switching one (see old code)
    {
    public:
        /// Creates a new value.
        Value(Type const& type, size_t value);

        /// Create a boolean value.
        static utility::Shared<Value> makeBool(bool value);

        /// Create a unit value.
        static utility::Shared<Value> makeUnit();

        /// Create a size value.
        static utility::Shared<Value> makeSize(size_t value);

        /// Create a default value of the given type.
        static utility::Shared<Value> makeDefault(Type const& type);

        [[nodiscard]] Type const& type() const;
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] bool getBool() const;
        [[nodiscard]] size_t getSize() const;

        [[nodiscard]] utility::Shared<Value> clone() const;

      private:
        Type const& type_;
        size_t      value_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Value const& value);

#endif
