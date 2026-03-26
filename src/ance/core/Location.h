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

        /// Create a nowhere location. A nowhere location is used for code that does not have a location.
        /// \return A nowhere location.
        static Location nowhere();// todo: possibly remove with Optional<Location> as soon as language has Optional

        /// Create a project location. A project location is used for code that is associated with a project but not an actual source location.
        /// \return A project location.
        static Location project();

        /// Create a core location. A core location is used for generated language core definitions.
        /// \return A core location.
        static Location core();

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

        /// Get whether this location is a nowhere location, meaning it does not have a location.
        /// \return True if it is a nowhere location.
        [[nodiscard]] bool isNowhere() const;

        /// Get whether this location is targeting a project.
        /// \return True if it is a project location.
        [[nodiscard]] bool isProject() const;

        /// Get whether this location is for core code.
        /// \return True if it is a core location.
        [[nodiscard]] bool isCore() const;

        /// Get whether this location is a file location, meaning it targets an entire file.
        /// \return True if it is a file location.
        /// \note A global or simple location is not considered a file location.
        [[nodiscard]] bool isFile() const;

        /// Get whether this location is on a single line.
        /// \return True if it is on a single line.
        [[nodiscard]] bool isSingleLine() const;

        /// Extend this location to include another location.
        /// If the locations are in different files, the location is not extended.
        /// \param location The location to extend to.
        void extend(Location const& location);

        /// Get a location describing the first position of this location.
        [[nodiscard]] Location first() const;

        /// Get a location describing the last position of this location.
        [[nodiscard]] Location last() const;

        /// Get the first location of two locations.
        /// \return The first location.
        static Location getFirst(Location const& a, Location const& b);

        bool operator==(Location const& location) const = default;

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
