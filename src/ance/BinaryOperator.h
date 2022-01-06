#ifndef ANCE_SRC_ANCE_BINARYOPERATOR_H_
#define ANCE_SRC_ANCE_BINARYOPERATOR_H_

#include <string>

/**
 * Any binary operator.
 */
class BinaryOperator
{
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
        NOT_EQUAL
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

  private:
    Value value_;
};

#endif
