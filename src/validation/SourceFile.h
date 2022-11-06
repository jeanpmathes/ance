#ifndef ANCE_SRC_VALIDATION_SOURCEFILE_H_
#define ANCE_SRC_VALIDATION_SOURCEFILE_H_

#include <filesystem>
#include <vector>

/**
 * Represents a source code file and stores the content in memory.
 */
class SourceFile
{
  public:
    /**
     * Create a source file from a file in the file system.
     * @param project_directory The project directory.
     * @param file The path to the file from the project directory.
     */
    SourceFile(const std::filesystem::path& project_directory, const std::filesystem::path& file);

    SourceFile(const SourceFile& other) = delete;
    SourceFile(SourceFile&& other)      = delete;

    /**
     * Get a string view of a source line.
     * @param line The line number, starting from 1.
     * @return A view of the line.
     */
    [[nodiscard]] std::string_view getLine(size_t line) const;

    /**
     * Get a string view of a slice of a line.
     * @param line The line number.
     * @param column_start The first column to include, starting with index 1.
     * @param column_end The last column to include.
     * @return A view of the slice.
     */
    [[nodiscard]] std::string_view getLineSlice(size_t line, unsigned int column_start, unsigned int column_end) const;

    /**
     * Get the path to the source file.
     * @return The path, relative to the project directory.
     */
    [[nodiscard]] const std::filesystem::path& getRelativePath() const;

    /**
     * Get the path from the project directory to the directory containing the source file.
     * @return The path to the directory.
     */
    [[nodiscard]] std::filesystem::path getDirectory() const;

    /**
     * Get the file name.
     * @return The file name.
     */
    [[nodiscard]] std::filesystem::path getFilename() const;

  private:
    std::vector<std::string> lines_;
    std::filesystem::path    relative_path_;
};

#endif

