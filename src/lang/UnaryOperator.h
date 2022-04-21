#ifndef ANCE_SRC_LANG_UNARYOPERATOR_H_
#define ANCE_SRC_LANG_UNARYOPERATOR_H_

#include <string>

namespace lang
{
    /**
    * Any unary operator.
    */
    class UnaryOperator
    {
      public:
        enum Value
        {
            /**
             * The logical not operator.
             */
            NOT,
        };

        UnaryOperator() = default;
        constexpr UnaryOperator(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] std::string toString() const;

      private:
        Value value_;
    };
}

#endif
