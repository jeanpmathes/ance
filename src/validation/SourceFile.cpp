#include "SourceFile.h"

#include <fstream>
#include <string>

SourceFile::SourceFile(const std::filesystem::path& project_directory, const std::filesystem::path& file) : path_(file)
{
    std::filesystem::path full_path = project_directory / file;

    std::ifstream file_stream(full_path);

    for (std::string line; std::getline(file_stream, line);) { lines_.push_back(std::move(line)); }

    file_stream.close();
}

std::string_view SourceFile::getLine(size_t line) const
{
    return std::string_view(lines_[line - 1]);
}

std::string_view SourceFile::getLineSlice(size_t line, unsigned int column_start, unsigned int column_end) const
{
    column_start--;
    column_end--;

    unsigned int length = column_end - column_start + 1;
    return getLine(line).substr(column_start, length);
}

const std::filesystem::path& SourceFile::getPath() const
{
    return path_;
}
