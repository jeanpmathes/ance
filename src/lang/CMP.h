#ifndef ANCE_SRC_LANG_CMP_H_
#define ANCE_SRC_LANG_CMP_H_

#include <cstdint>
#include <string>

class Storage;

namespace lang
{
    /**
     * Describes modes of compile-time execution.
     */
    class CMP
    {
      public:
        enum Value : uint8_t
        {
            /**
             * Code that cannot be executed at compile time.
             */
            NO_CMP,

            /**
             * Code that can be executed at compile time and at runtime.
             */
            OPTIONAL_CMP,

            /**
             * Code that can only be executed at compile time.
             */
            ONLY_CMP,

            /**
             * Invalid value.
             */
            INVALID
        };

        CMP() = default;
        constexpr CMP(Value value) : value_(value) {}// NOLINT(google-explicit-constructor)

        operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        [[nodiscard]] bool isRuntime() const;
        [[nodiscard]] bool isCompileTime() const;

        /**
         * Get a strict version of this CMP.
         * @return If already strict, returns itself, else returns ONLY_CMP.
         */
        [[nodiscard]] lang::CMP strict() const;

        /**
         * Get a string representation of this CMP.
         * @return The string representation.
         */
        [[nodiscard]] std::string toString() const;

        lang::CMP operator&(lang::CMP other) const;

        /**
         * Perform storage synchronization.
         */
        static void synchronize(lang::CMP* cmp, Storage& storage);

      private:
        Value value_;
    };
}

#endif
