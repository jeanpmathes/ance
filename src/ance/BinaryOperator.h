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
         * The mathematical modulo operator.
         */
        MODULO
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
