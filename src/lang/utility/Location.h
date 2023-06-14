#ifndef ANCE_SRC_LANG_UTILITY_LOCATION_H_
#define ANCE_SRC_LANG_UTILITY_LOCATION_H_

#include <llvm/IR/DebugLoc.h>

class CompileContext;

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
         * @param file_index The index of the file the location is in.
         */
        Location(size_t start_line, size_t start_column, size_t end_line, size_t end_column, size_t file_index);

        /**
         * Create a global location. A global location is used for code that is not in a source file.
         * @return A global location.
         */
        static Location global();

        /**
         * Get the line number.
         * @return The line number.
         */
        [[nodiscard]] size_t line() const;

        /**
         * Get the column number.
         * @return The column number.
         */
        [[nodiscard]] size_t column() const;

        /**
         * Get the last column of this location.
         * @return The last column number. Can be equal to column for single character locations.
         */
        [[nodiscard]] size_t columnEnd() const;

        /**
         * Get the file index of this location.
         * @return The file index.
         */
        [[nodiscard]] size_t file() const;

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
        llvm::DebugLoc getDebugLoc(llvm::LLVMContext& llvm_context, llvm::DIScope* scope) const;

        /**
         * Extend this location to include another location.
         * @param location The location to extend to.
         */
        void extend(lang::Location location);

        /**
         * Get the first location of two locations.
         * If any of the locations is global, the other location is returned.
         * If the locations are in different files, the location a is returned.
         * @return The first location.
         */
        static lang::Location getFirst(lang::Location a, lang::Location b);

        /*
         * Format this location as a string, in the format "file:line:column".
         */
        std::string toString(CompileContext& context);

        friend std::ostream& operator<<(std::ostream& os, lang::Location const& location);

      private:
        size_t                  start_line_;
        size_t                  start_column_;
        [[maybe_unused]] size_t end_line_;
        [[maybe_unused]] size_t end_column_;
        size_t                  file_index_;
    };
}

#endif
