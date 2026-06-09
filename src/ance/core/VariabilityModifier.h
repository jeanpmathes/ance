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

            /// Varying of the value is not allowed.
            /// This should be the default.
            INVARIABLE
        };

        VariabilityModifier() = default;
        constexpr VariabilityModifier(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /// Get this variability modifier as a string.
        /// @return The string.
        [[nodiscard]] std::string toString() const;

        bool isVariable() const;

      private:
        Value value_;
    };
}

#endif
