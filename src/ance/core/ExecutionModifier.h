#ifndef ANCE_CORE_EXECUTIONMODIFIER_H
#define ANCE_CORE_EXECUTIONMODIFIER_H

#include <string>

class Storage;

namespace ance::core
{
    /// Represents different execution modes for functions, variables and other things.
    class ExecutionModifier
    {
      public:
        enum Value : uint8_t
        {
            /// The code will run at compile-time.
            /// This means it can only call code that is able to run at compile-time.
            /// This code can be called from any other code.
            COMPILETIME_EXECUTION,

            /// The code will run at runtime.
            /// This means it can only call code that is able to run at runtime.
            /// This code can only be called from runtime code.
            RUNTIME_EXECUTION,

            /// The code can run at compile-time and runtime.
            /// This means it can only call code that is able to run at compile-time and runtime.
            /// This code can be called from any other code.
            ANY_EXECUTION,
        };

        ExecutionModifier() = default;
        constexpr ExecutionModifier(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

                 /// Get this execution mode as a string.
                 /// @return The string.
                 [[nodiscard]] std::string toString() const;

      private:
        Value value_;
    };
}

#endif
