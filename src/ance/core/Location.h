#ifndef ANCE_CORE_LOCATION_H
#define ANCE_CORE_LOCATION_H

#include <ostream>

namespace ance::core
{

    /// A location in a source file.
    class Location
    {
      public:
        /// Create a source file location.
        /// \param start_line The line number of the start of the location. Actual line numbers start with 1, not 0.
        /// \param start_column The column number of the start of the location.
        /// \param end_line The line end of the location.
        /// \param end_column The column end of the location.
        /// \param file_index The index of the file the location is in.
        Location(size_t start_line, size_t start_column, size_t end_line, size_t end_column, size_t file_index);

        /// Create a global location. A global location is used for code that is not in a source file.
        /// \return A global location.
        static Location global();

        /// Create a file location. It targets an entire file.
        /// \param file_index The index of the file.
        /// \return The location.
        static Location file(size_t file_index);

        /// Create a simple location. It targets a single code point.
        /// \param line The line number.
        /// \param column The column number.
        /// \param file_index The index of the file.
        /// \return The location.
        static Location simple(size_t line, size_t column, size_t file_index);

        /// Get the line number.
        /// \return The line number.
        [[nodiscard]] size_t line() const;

        /// Get the column number.
        /// \return The column number.
        [[nodiscard]] size_t column() const;

        /// Get the last line of this location.
        /// \return The last line number. Can be equal to line for single line locations.
        [[nodiscard]] size_t lineEnd() const;

        /// Get the last column of this location.
        /// \return The last column number. Can be equal to column for single character locations.
        [[nodiscard]] size_t columnEnd() const;

        /// Get the file index of this location.
        /// \return The file index.
        [[nodiscard]] size_t fileIndex() const;

        /// Get whether this location is global, meaning not an actual source location.
        /// \return True if it is global.
        [[nodiscard]] bool isGlobal() const;

        /// Get whether this location is a file location, meaning it targets an entire file.
        /// \return True if it is a file location.
        /// \note A global or simple location is not considered a file location.
        [[nodiscard]] bool isFile() const;

        /// Get whether this location is on a single line.
        /// \return True if it is on a single line.
        [[nodiscard]] bool isSingleLine() const;

        /// Extend this location to include another location.
        /// If this is a global or file location, it will be set to the passed location.
        /// \param location The location to extend to.
        void extend(Location const& location);

        /// Get a location describing the first position of this location.
        [[nodiscard]] Location first() const;

        /// Get a location describing the last position of this location.
        [[nodiscard]] Location last() const;

        /// Get the first location of two locations.
        /// If any of the locations is global, the other location is returned.
        /// If the locations are in different files, the first argument is returned.
        /// \return The first location.
        static Location getFirst(Location a, Location b);

        friend std::ostream& operator<<(std::ostream& os, Location const& location);

      private:
        size_t start_line_;
        size_t start_column_;
        size_t end_line_;
        size_t end_column_;
        size_t file_index_;
    };
}

#endif
