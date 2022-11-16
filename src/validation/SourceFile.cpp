#include "SourceFile.h"

#include <fstream>
#include <string>

#include <boost/locale/utf.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>

SourceFile::SourceFile(std::filesystem::path const& project_directory, std::filesystem::path const& file)
    : relative_path_(file)
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

std::filesystem::path const& SourceFile::getRelativePath() const
{
    return relative_path_;
}

std::filesystem::path SourceFile::getDirectory() const
{
    return relative_path_.parent_path();
}

std::filesystem::path SourceFile::getFilename() const
{
    return relative_path_.filename();
}

size_t SourceFile::getUtf8Index(size_t line, size_t utf_32_column) const
{
    std::string_view line_view    = getLine(line);
    int              utf_8_column = 0;

    boost::u8_to_u32_iterator<std::string_view::const_iterator> utf_32_iterator(line_view.begin());

    for (size_t utf_32_index = 0; utf_32_index < utf_32_column; utf_32_index++)
    {
        utf_8_column += boost::locale::utf::utf_traits<char8_t>::width(*utf_32_iterator);
        utf_32_iterator++;
    }

    return static_cast<size_t>(utf_8_column);
}
