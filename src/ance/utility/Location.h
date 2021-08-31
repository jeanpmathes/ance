#ifndef ANCE_SRC_ANCE_UTILITY_LOCATION_H_
#define ANCE_SRC_ANCE_UTILITY_LOCATION_H_

#include <llvm/IR/DebugLoc.h>

namespace ance
{
    /**
     * A location in a source file.
     */
    class Location
    {
      public:
        /**
         * Create a source file location.
         * @param start_line The line number of the start of the location.
         * @param start_column The column number of the start of the location.
         * @param end_line The line end of the location.
         * @param end_column The column end of the location.
         */
        Location(unsigned int start_line, unsigned int start_column, unsigned int end_line, unsigned int end_column);

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
         * Get the debug location for this source location.
         * @param llvm_context The llvm context.
         * @param scope The containing debug scope.
         * @return The debug location.
         */
        llvm::DebugLoc getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope) const;

        friend std::ostream& operator<<(std::ostream& os, const ance::Location& location);

      private:
        unsigned                  start_line_;
        unsigned                  start_column_;
        [[maybe_unused]] unsigned end_line_;
        [[maybe_unused]] unsigned end_column_;
    };
}

#endif
