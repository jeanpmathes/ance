#include "SourceFile.h"

#include <fstream>
#include <string>

#include <boost/locale/utf.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>

ance::sources::SourceFile::SourceFile(std::filesystem::path const& base_directory, std::filesystem::path const& file, size_t index)
    : relative_path_(file), full_path_(base_directory / file), index_(index)
{
    std::ifstream file_stream(full_path_);

    for (std::string line; std::getline(file_stream, line);) { lines_.push_back(std::move(line)); }

    file_stream.close();

    lines_.emplace_back("");
}

std::string_view ance::sources::SourceFile::getLine(size_t line) const
{
    return std::string_view(lines_[line - 1]);
}

std::string_view ance::sources::SourceFile::getLineSlice(size_t line, unsigned int column_start, unsigned int column_end) const
{
    column_start--;
    column_end--;

    unsigned int const length = column_end - column_start + 1;
    return getLine(line).substr(column_start, length);
}

std::filesystem::path const& ance::sources::SourceFile::getRelativePath() const
{
    return relative_path_;
}

std::filesystem::path const& ance::sources::SourceFile::getFullPath() const
{
    return full_path_;
}

std::filesystem::path ance::sources::SourceFile::getDirectory() const
{
    return relative_path_.parent_path();
}

std::filesystem::path ance::sources::SourceFile::getFilename() const
{
    return relative_path_.filename();
}

size_t ance::sources::SourceFile::getUtf8Index(size_t const line, size_t const utf_32_column) const
{
    if (utf_32_column == 0) return 0;

    std::string_view const line_view    = getLine(line);
    int                    utf_8_column = 0;

    boost::u8_to_u32_iterator utf_32_iterator(line_view.begin());

    for (size_t utf_32_index = 0; utf_32_index < utf_32_column; utf_32_index++)
    {
        utf_8_column += boost::locale::utf::utf_traits<char8_t>::width(*utf_32_iterator);
        utf_32_iterator = std::next(utf_32_iterator);
    }

    return static_cast<size_t>(utf_8_column);
}

size_t ance::sources::SourceFile::index() const
{
    return index_;
}
