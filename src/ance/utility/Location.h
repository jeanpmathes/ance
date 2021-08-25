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
         * @param line The line number.
         * @param column The column number.
         */
        Location(unsigned line, unsigned column);

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

      private:
        unsigned line_;
        unsigned column_;
    };
}

#endif
