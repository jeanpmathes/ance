#include "FileContext.h"

#include "validation/SourceFile.h"

FileContext::FileContext(size_t file_index, SourceFile& source_file) : index_(file_index), source_file_(source_file) {}

size_t FileContext::getFileIndex() const
{
    return index_;
}

size_t FileContext::getUtf8Index(size_t line, size_t utf_32_column) const
{
    return source_file_.getUtf8Index(line, utf_32_column);
}
