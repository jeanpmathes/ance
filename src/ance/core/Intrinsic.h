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
             * This intrinsic does not take any parameters and returns the unit type.
             */
            NO_OPERATION,
            /**
             * This intrinsic takes the following parameters:
             * - The scope to declare the variable in.
             * - The identifier of the variable to declare.
             * - Whether the declaration is final.
             * - The type of the variable to declare.
             * It returns a reference to the declared variable.
             */
            DECLARE,// todo: make method on scope class
            /**
             * This intrinsic takes the following parameters:
             * - The scope to resolve the variable in.
             * - The identifier of the variable to resolve.
             * It returns a reference to the resolved variable.
             */
            RESOLVE,// todo: make method on scope class
            /**
             * This intrinsic takes the following parameters:
             * - The scope to get the parent of.
             * It returns the parent scope.
             */
            GET_PARENT,// todo: make method on scope class
            /**
             * This intrinsic takes the following parameters:
             * - The boolean to convert.
             * It returns the string representation of the boolean.
             */
            B_2_STR,// todo: implement as core function
            /**
             * This intrinsic takes the following parameters:
             * - The string message to log.
             * - The location to log the message at.
             * It returns the unit type.
             */
            LOG,
            /**
             * This intrinsic takes the following parameters:
             * - The path of the file to include.
             * - The location of a file to use as base to resolve a relative path.
             * It returns the unit type.
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
