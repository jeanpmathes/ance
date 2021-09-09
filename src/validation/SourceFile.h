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
     * @param path The path to the source file.
     */
    explicit SourceFile(const std::filesystem::path& path);

    SourceFile(const SourceFile& other) = delete;
    SourceFile(SourceFile&& other)      = delete;

    /**
     * Get a string view of a source line.
     * @param line The line number, starting from 1.
     * @return A view of the line.
     */
    [[nodiscard]] std::string_view getLine(unsigned int line) const;

    /**
     * Get a string view of a slice of a line.
     * @param line The line number.
     * @param column_start The first column to include, starting with index 1.
     * @param column_end The last column to include.
     * @return A view of the slice.
     */
    [[nodiscard]] std::string_view getLineSlice(unsigned int line,
                                                unsigned int column_start,
                                                unsigned int column_end) const;

  private:
    std::vector<std::string> lines_;
};

#endif
