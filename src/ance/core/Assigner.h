#ifndef ANCE_CORE_ASSIGNER_H
#define ANCE_CORE_ASSIGNER_H

#include <cstdint>
#include <string>

namespace ance::core
{
    /**
     * Defines an assignment operation.
     */
    class Assigner
    {
    public:
        enum Value : uint8_t
        {
            /**
             * A simple copy assignment.
             */
            COPY_ASSIGNMENT,
            /**
             * A final copy assignment.
             */
            FINAL_COPY_ASSIGNMENT,
            /**
             * A move assignment, which is a special assignment that copies and performs additional operations.
             * It has no obligation to leave the source value in a valid state, allowing an overall cheaper transfer.
             */
            MOVE_ASSIGNMENT,
            /**
             * An unspecified assignment. The actual assignment can be inferred from the used types.
             */
            UNSPECIFIED
        };

        Assigner() = default;
        constexpr Assigner(Value const val) : value_(val) {}// NOLINT(google-explicit-constructor)

        operator Value() const;// NOLINT(google-explicit-constructor)
        explicit operator bool() = delete;

        /**
         * Get whether this assignment is final.
         * @return True if this assignment is final.
         */
        [[nodiscard]] bool isFinal() const;

        /**
         * Get whether this assignment is represented by a symbol.
         * @return True if a symbol exists for this assignment.
         */
        [[nodiscard]] bool hasSymbol() const;

        /**
         * Get the symbol for this assignment.
         * @return The symbol for this assignment.
         */
        [[nodiscard]] std::string getSymbol() const;

    private:
        Value value_;
    };
}

#endif
