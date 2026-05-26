#ifndef ANCE_CORE_BINARYOPERATOR_H_
#define ANCE_CORE_BINARYOPERATOR_H_

#include <string>

namespace ance::core
{
    /// Any binary operator.
    class BinaryOperator
    {
      public:
        enum Value
        {
            /// Any unspecified operator, used as a default value for error handling and such.
            UNSPECIFIED,

            /// The addition operator.
            ADDITION,

            /// The subtraction operator.
            SUBTRACTION,

            /// The multiplication operator.
            MULTIPLICATION,

            /// The division operator.
            DIVISION,

            /// The remainder operator.
            REMAINDER,

            /// The less-than relational operator.
            LESS_THAN,

            /// The less-than-or-equal relational operator.
            LESS_THAN_OR_EQUAL,

            /// The greater-than relational operator.
            GREATER_THAN,

            /// The greater-than-or-equal relational operator.
            GREATER_THAN_OR_EQUAL,

            /// The equality operator.
            EQUAL,

            /// The inequality operator.
            NOT_EQUAL
        };

        BinaryOperator() = default;
        constexpr BinaryOperator(Value const value) : value_(value) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] std::string toString() const;
        [[nodiscard]] std::string toShortName() const;

      private:
        Value value_;
    };
}

#endif
