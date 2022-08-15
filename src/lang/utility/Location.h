#ifndef ANCE_SRC_LANG_UTILITY_LOCATION_H_
#define ANCE_SRC_LANG_UTILITY_LOCATION_H_

#include <llvm/IR/DebugLoc.h>

namespace lang
{
    /**
     * A location in a source file.
     */
    class Location
    {
      public:
        /**
         * Create a source file location.
         * @param start_line The line number of the start of the location. Actual line numbers start with 1, not 0.
         * @param start_column The column number of the start of the location.
         * @param end_line The line end of the location.
         * @param end_column The column end of the location.
         */
        Location(unsigned int start_line, unsigned int start_column, unsigned int end_line, unsigned int end_column);

        /**
         * Create a global location. A global location is used for code that is not in a source file.
         * @return A global location.
         */
        static Location global();

        /**
         * Get the line number.
         * @return The line number.
         */
        [[nodiscard]] unsigned line() const;

        /**
         * Get the column number.
         * @return The column number.
         */
        [[nodiscard]] unsigned column() const;

        /**
         * Get the last column of this location.
         * @return The last column number. Can be equal to column for single character locations.
         */
        [[nodiscard]] unsigned columnEnd() const;

        /**
         * Get whether this location is global, meaning not an actual source location.
         * @return True if it is global.
         */
        [[nodiscard]] bool isGlobal() const;

        /**
         * Get whether this location is on a single line.
         * @return True if it is on a single line.
         */
        [[nodiscard]] bool isSingleLine() const;

        /**
         * Get the debug location for this source location.
         * @param llvm_context The llvm context.
         * @param scope The containing debug scope.
         * @return The debug location.
         */
        llvm::DebugLoc getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope) const;

        /**
         * Extend this location to include another location.
         * @param location The location to extend to.
         */
        void extend(lang::Location location);

        friend std::ostream& operator<<(std::ostream& os, const lang::Location& location);

      private:
        unsigned                  start_line_;
        unsigned                  start_column_;
        [[maybe_unused]] unsigned end_line_;
        [[maybe_unused]] unsigned end_column_;
    };
}

#endif
