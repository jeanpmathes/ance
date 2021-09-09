#include "SourceFile.h"

#include <fstream>
#include <string>

SourceFile::SourceFile(const std::filesystem::path& path)
{
    std::ifstream file(path);

    for (std::string line; std::getline(file, line);) { lines_.push_back(std::move(line)); }

    file.close();
}

std::string_view SourceFile::getLine(unsigned int line) const
{
    return std::string_view(lines_[line - 1]);
}

std::string_view SourceFile::getLineSlice(unsigned int line, unsigned int column_start, unsigned int column_end) const
{
    column_start--;
    column_end--;

    unsigned int length = column_end - column_start + 1;
    return getLine(line).substr(column_start, length);
}
