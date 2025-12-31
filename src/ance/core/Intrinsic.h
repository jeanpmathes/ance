#ifndef ANCE_CORE_INTRINSIC_H
#define ANCE_CORE_INTRINSIC_H

#include <ostream>

#include "ance/utility/Node.h"

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// Any intrinsic operation.
    class Intrinsic
    {
      public:
        enum Value
        {
            /**
             * This intrinsic does nothing.
             */
            NO_OPERATION,
            /**
             * This intrinsic declares a variable in a scope.
             */
            DECLARE,// todo: make method on scope class
            /**
             * This intrinsic resolves a variable in a scope.
             */
            RESOLVE,// todo: make method on scope class
            /**
             * This intrinsic gets the parent scope of a scope.
             */
            GET_PARENT,// todo: make method on scope class
            /**
             * This intrinsic converts a boolean to a string.
             */
            B_2_STR,// todo: implement as core function
            /**
             * This intrinsic logs a string to the compiler log.
             */
            LOG,
            /**
             * This intrinsic includes another source file.
             */
            INCLUDE
        };

        Intrinsic() = default;
        constexpr Intrinsic(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] Value       value() const;
        [[nodiscard]] Identifier  identifier() const;
        [[nodiscard]] std::string toString() const;

      private:
        Value value_;
    };
}

#endif
