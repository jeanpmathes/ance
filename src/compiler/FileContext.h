#ifndef ANCE_SRC_COMPILER_FILECONTEXT_H_
#define ANCE_SRC_COMPILER_FILECONTEXT_H_

/**
 * The file in which context current elements are defined.
 */
class FileContext
{
  public:
    explicit FileContext(size_t file_index);

    /**
     * Get the index of the file.
     * @return The index of the file.
     */
    size_t getFileIndex() const;

  private:
    size_t index_;
};

#endif
