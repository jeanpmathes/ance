#ifndef ANCE_CORE_LITERALTYPE_H
#define ANCE_CORE_LITERALTYPE_H

#include <string>

namespace ance::core
{
    /// Built-in types supported as literals in the source code.
    class LiteralType
    {
      public:
        enum Value
        {
            Bool,
            Unit,
            Size,
            String,
            Type,
        };

        LiteralType() = default;
        constexpr LiteralType(Value const val) : value_(val) {}
        operator Value() const;
        explicit operator bool() = delete;

        [[nodiscard]] std::string toString() const;

      private:
        Value value_{};
    };
}

#endif
