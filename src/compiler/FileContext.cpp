
#include "FileContext.h"

FileContext::FileContext(size_t file_index) : index_(file_index) {}

size_t FileContext::getFileIndex() const
{
    return index_;
}
