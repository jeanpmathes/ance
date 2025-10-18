#ifndef ANCE_CORE_ACCESSMODIFIER_H
#define ANCE_CORE_ACCESSMODIFIER_H

#include <string>

class Storage;

namespace ance::core
{
    /**
     * Represents different access levels of declared entities.
     */
    class AccessModifier
    {
      public:
        enum Value : uint8_t
        {
            PUBLIC_ACCESS,
            PRIVATE_ACCESS,
            EXTERN_ACCESS
        };

        AccessModifier() = default;
        constexpr AccessModifier(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

        operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /**
         * Get this access modifier as string.
         * @return The string.
         */
        [[nodiscard]] std::string toString() const;

      private:
        Value value_;
    };
}

#endif
