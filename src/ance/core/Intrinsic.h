#ifndef ANCE_CORE_INTRINSIC_H
#define ANCE_CORE_INTRINSIC_H

#include <optional>
#include <ostream>

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// Any intrinsic operation.
    class Intrinsic
    {
      public:
        enum Value
        {
            /// Does nothing.
            ///
            /// This intrinsic does not take any parameters and returns the unit type.
            NO_OPERATION,

            /// Declares a variable in a scope.
            ///
            /// This intrinsic takes the following parameters:
            /// - The scope to declare the variable in.
            /// - The identifier of the variable to declare.
            /// - Whether the declaration is final.
            /// - The type of the variable to declare.
            ///
            /// It returns a reference to the declared variable.
            DECLARE,// todo: after compilation: maybe this should be a method on scope

            /// Finds a variable in the chain of scopes and provides a reference to it.
            ///
            /// This intrinsic takes the following parameters:
            /// - The scope to resolve the variable in.
            /// - The identifier of the variable to resolve.
            ///
            /// It returns a reference to the resolved variable.
            RESOLVE,// todo: after compilation: maybe this should be a method on scope

            /// Erases a variable from a scope, making it inaccessible for future lookups.
            ///
            /// This intrinsic takes the following parameters:
            /// - The scope to erase the variable from.
            /// - The identifier of the variable to erase.
            ///
            /// It returns the unit type.
            ERASE,// todo: after compilation: maybe this should be a method on scope

            /// Provides access to the parent scope of a scope.
            ///
            /// This intrinsic takes the following parameters:
            /// - The scope to get the parent of.
            ///
            /// It returns the parent scope.
            GET_PARENT,// todo: after compilation: maybe this should be a method on scope

            /// Converts a boolean value to its string representation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The boolean to convert.
            ///
            /// It returns the string representation of the boolean.
            B_2_STR,// todo: implement as core function

            /// Converts a half precision float value to its string representation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The half precision float to convert.
            ///
            /// It returns the string representation of the float.
            FH_2_STR,// todo: implement as core function

            /// Converts a single precision float value to its string representation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The single precision float to convert.
            ///
            /// It returns the string representation of the float.
            FS_2_STR,// todo: implement as core function

            /// Converts a double precision float value to its string representation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The double precision float to convert.
            ///
            /// It returns the string representation of the float.
            FD_2_STR,// todo: implement as core function

            /// Converts a quad precision float value to its string representation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The quad precision float to convert.
            ///
            /// It returns the string representation of the float.
            FQ_2_STR,// todo: implement as core function

            /// Computes logical negation of a boolean value.
            ///
            /// This intrinsic takes the following parameters:
            /// - The boolean to negate.
            ///
            /// It returns the negated boolean.
            BOOL_NOT,

            /// Logs a string message as compiler output.
            ///
            /// This intrinsic takes the following parameters:
            /// - The string message to log.
            /// - The location to log the message at.
            ///
            /// It returns the unit type.
            LOG,

            /// Includes a file into the current compilation.
            ///
            /// This intrinsic takes the following parameters:
            /// - The path of the file to include.
            /// - The location of a file to use as base to resolve a relative path.
            ///
            /// It returns the unit type.
            INCLUDE,

            /// Calls an intrinsic by its string name.
            /// This is a variadic intrinsic: only the first parameter is typed, the rest are untyped.
            ///
            /// This intrinsic takes the following parameters:
            /// - The name of the intrinsic to call (string).
            /// - Any number of additional arguments to pass to the intrinsic.
            ///
            /// It returns the result of the called intrinsic.
            CALL_INTRINSIC,// todo: remove variadic parameters, instead take a string and a list of arguments

            SIZE_ADD,
            SIZE_SUB,
            SIZE_MUL,
            SIZE_DIV,
            SIZE_REM,

            HALF_ADD,// todo: maybe these can be made generic in the same way that integer ops are, just not over bit size but precisions
            HALF_SUB,
            HALF_MUL,
            HALF_DIV,
            HALF_REM,

            SINGLE_ADD,
            SINGLE_SUB,
            SINGLE_MUL,
            SINGLE_DIV,
            SINGLE_REM,

            DOUBLE_ADD,
            DOUBLE_SUB,
            DOUBLE_MUL,
            DOUBLE_DIV,
            DOUBLE_REM,

            QUAD_ADD,
            QUAD_SUB,
            QUAD_MUL,
            QUAD_DIV,
            QUAD_REM
        };

        Intrinsic() = default;
        constexpr Intrinsic(Value const value) : value_(value) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] Value       value() const;
        [[nodiscard]] Identifier  identifier() const;
        [[nodiscard]] std::string toString() const;

        /// Attempts to look up an intrinsic by its string name.
        static std::optional<Intrinsic> fromString(std::string const& name);

      private:
        Value value_;
    };
}

#endif
