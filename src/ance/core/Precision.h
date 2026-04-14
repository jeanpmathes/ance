#ifndef ANCE_CORE_PRECISION_H
#define ANCE_CORE_PRECISION_H

#include <cstdint>
#include <string>

namespace llvm
{
    struct fltSemantics;
}

namespace ance::core
{
    /**
     * Defines floating-point precision.
     */
    class Precision
    {
      public:
        enum Value : uint8_t
        {
            /**
             * Half-precision, meaning 16 bit.
             */
            HALF,

            /**
             * Single-precision, meaning 32 bit.
             */
            SINGLE,

            /**
             * Double-precision, meaning 64 bit.
             */
            DOUBLE,

            /**
             * Quadruple-precision, meaning 128 bit.
             */
            QUAD,
        };

        Precision() = default;
        constexpr Precision(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

                 operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        static Precision get(llvm::fltSemantics const& semantics);
        llvm::fltSemantics const& getLlvmSemantics() const;

        /**
         * Get the suffix for this precision.
         * @return The suffix for this precision.
         */
        [[nodiscard]] std::string getSuffix() const;

      private:
        Value value_;
    };
}

#endif
