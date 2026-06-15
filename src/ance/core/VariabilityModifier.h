#ifndef ANCE_CORE_VARIABILITYMODIFIER_H
#define ANCE_CORE_VARIABILITYMODIFIER_H

#include <string>

class Storage;

namespace ance::core
{
    /// Represents whether a value can vary.
    /// This can, for example, be used for variables, but also for references.
    class VariabilityModifier
    {
      public:
        enum Value : uint8_t
        {
            /// Varying of the value is allowed.
            VARIABLE,

            /// Varying of the value is not allowed, it is a constant.
            /// This should be the default.
            CONSTANT
        };

        VariabilityModifier() = default;
        constexpr VariabilityModifier(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /// Get this variability modifier as a string.
        /// @return The string.
        [[nodiscard]] std::string toString() const;

        /// Get the keyword used as part of a binding to get this variability.
        /// @return The string.
        [[nodiscard]] std::string toBindingKeyword() const;

        [[nodiscard]] bool isVariable() const;
        [[nodiscard]] bool isConstant() const;

      private:
        Value value_;
    };
}

#endif
