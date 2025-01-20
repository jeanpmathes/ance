#include "SourceFile.h"

#include <fstream>
#include <string>

#include <boost/locale/encoding.hpp>

ance::sources::SourceFile::SourceFile(std::filesystem::path const& base_directory, std::filesystem::path const& file, size_t index)
    : relative_path_(file), full_path_(base_directory / file), index_(index)
{
    std::ifstream file_stream(full_path_);

    for (std::string line; std::getline(file_stream, line);)
    {
        lines_.emplace_back(boost::locale::conv::utf_to_utf<char32_t>(line));
    }

    file_stream.close();

    lines_.emplace_back(U"");
}

std::u32string_view ance::sources::SourceFile::getLine(size_t line) const
{
    return std::u32string_view(lines_[line - 1]);
}

std::u32string_view ance::sources::SourceFile::getLineSlice(size_t const line, unsigned int column_start, unsigned int column_end) const
{
    column_start -= 1;
    column_end -= 1;

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

size_t ance::sources::SourceFile::index() const
{
    return index_;
}
