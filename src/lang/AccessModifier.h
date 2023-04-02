#ifndef ANCE_SRC_LANG_ACCESSMODIFIER_H_
#define ANCE_SRC_LANG_ACCESSMODIFIER_H_

#include <llvm/IR/GlobalValue.h>

class Storage;

namespace lang
{
    /**
     * Represents different access levels of named values.
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
        constexpr AccessModifier(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /**
         * Get this access modifier as string.
         * @return The string.
         */
        [[nodiscard]] std::string toString() const;

        /**
         * Get the corresponding native linkage type.
         * @return The linkage type.
         */
        llvm::GlobalValue::LinkageTypes linkage();

        /**
         * Perform storage synchronization.
         */
        static void synchronize(lang::AccessModifier* access_modifier, Storage& storage);

      private:
        Value value_;
    };
}

#endif
