#ifndef ANCE_SRC_COMPILER_FILECONTEXT_H_
#define ANCE_SRC_COMPILER_FILECONTEXT_H_

#include <cstddef>

class SourceFile;

/**
 * The file in which context current elements are defined.
 */
class FileContext
{
  public:
    explicit FileContext(size_t file_index, SourceFile& source_file);

    /**
     * Get the index of the file.
     * @return The index of the file.
     */
    [[nodiscard]] size_t getFileIndex() const;

    /**
     * Get the UTF-8 column index for a given UTF-32 column index.
     * @param line The line index.
     * @param utf_32_column The UTF-32 column index.
     * @return The UTF-8 column index.
     */
    [[nodiscard]] size_t getUtf8Index(size_t line, size_t utf_32_column) const;

  private:
    size_t      index_;
    SourceFile& source_file_;
};

#endif
