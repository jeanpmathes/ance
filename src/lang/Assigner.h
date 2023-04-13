#ifndef ANCE_SRC_LANG_ASSIGNER_H_
#define ANCE_SRC_LANG_ASSIGNER_H_

#include <string>

class Storage;

namespace lang
{
    /**
     * Represents an assignment operation.
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
             * A move assignment, which is a special assignment that copies and performs additional operations.
             */
            MOVE_ASSIGNMENT,
            /**
             * A final copy assignment.
             */
            FINAL_COPY_ASSIGNMENT,
            /**
             * A reference binding assignment.
             */
            REFERENCE_BINDING,
            /**
             * An unspecified assignment. The actual assignment can be inferred from the used types.
             */
            UNSPECIFIED
        };

        Assigner() = default;
        constexpr Assigner(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

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

        /**
         * Perform storage synchronization.
         */
        static void synchronize(lang::Assigner* assigner, Storage& storage);

      private:
        Value value_;
    };
}

#endif
