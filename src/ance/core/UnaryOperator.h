#ifndef ANCE_CORE_UNARYOPERATOR_H_
#define ANCE_CORE_UNARYOPERATOR_H_

#include <string>

namespace ance::core
{
    /// Any unary operator.
    class UnaryOperator
    {
    public:
        enum Value
        {
            /// The logical not operator.
            NOT,
        };

        UnaryOperator() = default;
        constexpr UnaryOperator(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

        operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] std::string toString() const;

    private:
        Value value_;
    };
}

#endif
