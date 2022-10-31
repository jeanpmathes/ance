#ifndef ANCE_SRC_LANG_BINARYOPERATOR_H_
#define ANCE_SRC_LANG_BINARYOPERATOR_H_

#include <string>

namespace lang
{
    /**
    * Any binary operator.
    */
    class BinaryOperator
    {
      private:
        enum class Category
        {
            ARITHMETIC,
            RELATIONAL,
            EQUALITY,
            BITWISE,
            BITWISE_SHIFT,
        };

      private:
        [[nodiscard]] Category getCategory() const;

      public:
        enum Value
        {
            /**
            * The mathematical addition operator.
            */
            ADDITION,
            /**
            * The mathematical subtraction operator.
            */
            SUBTRACTION,
            /**
            * The mathematical multiplication operator.
            */
            MULTIPLICATION,
            /**
            * The mathematical division operator.
            */
            DIVISION,
            /**
            * The mathematical remainder operator.
            */
            REMAINDER,
            /**
            * The mathematical less-than relational operator.
            */
            LESS_THAN,
            /**
            * The mathematical less-than-or-equal relational operator.
            */
            LESS_THAN_OR_EQUAL,
            /**
            * The mathematical greater-than relational operator.
            */
            GREATER_THAN,
            /**
            * The mathematical greater-than-or-equal relational operator.
            */
            GREATER_THAN_OR_EQUAL,
            /**
            * The equality relational operator.
            */
            EQUAL,
            /**
            * The inequality relational operator.
            */
            NOT_EQUAL,
            /**
             * The bitwise and operator.
             */
            BITWISE_AND,
            /**
             * The bitwise or operator.
             */
            BITWISE_OR,
            /**
             * The bitwise xor operator.
             */
            BITWISE_XOR,
            /**
             * The bitwise left shift operator.
             */
            SHIFT_LEFT,
            /**
             * The bitwise right shift operator.
             */
            SHIFT_RIGHT
        };

        BinaryOperator() = default;
        constexpr BinaryOperator(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /**
         * Get a string representation of the operator.
         * @return The string representation.
         */
        [[nodiscard]] std::string toString() const;

        /**
         * Whether the operator is a relational operator, excluding equality. A relational operator commonly returns a boolean value.
         * @return True if the operator is a relational operator, false otherwise.
         */
        [[nodiscard]] bool isRelational() const;
        /**
         * Whether the operator is an equality relational operator. An equality relational operator returns a boolean value.
         * @return True if the operator is an equality relational operator, false otherwise.
         */
        [[nodiscard]] bool isEquality() const;
        /**
         * Whether the operator is an arithmetic operator. An arithmetic operator commonly returns a value of similar type as its operands.
         * @return True if the operator is an arithmetic operator, false otherwise.
         */
        [[nodiscard]] bool isArithmetic() const;
        /**
         * Whether the operator is a bitwise operator. A bitwise operator commonly returns a value of similar type as its operands.
         * @return True if the operator is a bitwise operator, false otherwise.
         */
        [[nodiscard]] bool isBitwise() const;
        /**
         * Whether the operator is a shift operator. A shift operator commonly returns a value of similar type as its operands.
         * @return True if the operator is a shift operator, false otherwise.
         */
        [[nodiscard]] bool isShift() const;

      private:
        Value value_;
    };
}

#endif

