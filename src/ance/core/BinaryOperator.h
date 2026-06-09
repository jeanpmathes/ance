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
            UNSPECIFIED,// todo: remove, replace with optional in AST/EST

            /// The addition operator, adding two (numerical) values.
            ADDITION,

            /// The subtraction operator, subtracting one (numerical) value from another.
            SUBTRACTION,

            /// The multiplication operator, multiplying two (numerical) values.
            MULTIPLICATION,

            /// The division operator, dividing one (numerical) value by another.
            DIVISION,

            /// The remainder operator, returning the remainder of a division.
            /// Note that this is different from the modulus.
            REMAINDER,

            /// The less-than relational operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
            LESS_THAN,

            /// The less-than-or-equal relational operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
            LESS_THAN_OR_EQUAL,

            /// The greater-than relational operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
            GREATER_THAN,

            /// The greater-than-or-equal relational operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
            GREATER_THAN_OR_EQUAL,

            /// The equality operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
            EQUAL,

            /// The inequality operator.
            /// All four relational operators and the equality and inequality operator fulfill a common contract.
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
