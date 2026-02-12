#include "Location.h"

#include <cassert>
#include <iostream>

namespace
{
    enum MODE : size_t
    {
        MODE_GLOBAL = 0,
        MODE_FILE   = 1,
    };
}

ance::core::Location::Location(size_t start_line, size_t start_column, size_t end_line, size_t end_column, size_t file_index)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
    , file_index_(file_index)
{}

ance::core::Location ance::core::Location::global()
{
    return {0, 0, MODE_GLOBAL, 0, 0};
}

ance::core::Location ance::core::Location::file(size_t file_index)
{
    return {0, 0, MODE_FILE, 0, file_index};
}

ance::core::Location ance::core::Location::simple(size_t line, size_t column, size_t file_index)
{
    assert(line > 0);

    return {line, column, line, column, file_index};
}

size_t ance::core::Location::line() const
{
    return start_line_;
}

size_t ance::core::Location::column() const
{
    return start_column_;
}

size_t ance::core::Location::columnEnd() const
{
    return end_column_;
}

size_t ance::core::Location::fileIndex() const
{
    return file_index_;
}

bool ance::core::Location::isGlobal() const
{
    return start_line_ == 0 && end_line_ == MODE_GLOBAL;
}

bool ance::core::Location::isFile() const
{
    return start_line_ == 0 && end_line_ == MODE_FILE;
}

bool ance::core::Location::isSingleLine() const
{
    return start_line_ == end_line_ && !isGlobal() && !isFile();
}

void ance::core::Location::extend(Location const& location)
{
    if (this->isGlobal() || this->isFile())
    {
        *this = location;
        return;
    }

    if (location.isGlobal())
    {
        return;
    }

    assert(location.fileIndex() == fileIndex());

    if (location.isFile())
    {
        *this = location;
        return;
    }

    if (location.start_line_ < start_line_ || (location.start_line_ == start_line_ && location.start_column_ < start_column_))
    {
        start_line_   = location.start_line_;
        start_column_ = location.start_column_;
    }

    if (location.end_line_ > end_line_ || (location.end_line_ == end_line_ && location.end_column_ > end_column_))
    {
        end_line_   = location.end_line_;
        end_column_ = location.end_column_;
    }
}

ance::core::Location ance::core::Location::first() const
{
    if (isGlobal() || isFile()) return *this;

    return Location(start_line_, start_column_, start_line_, start_column_, file_index_);
}

ance::core::Location ance::core::Location::last() const
{
    if (isGlobal() || isFile()) return *this;

    return Location(end_line_, end_column_, end_line_, end_column_, file_index_);
}

ance::core::Location ance::core::Location::getFirst(Location a, Location b)
{
    if (b.isGlobal()) return a;
    if (a.isGlobal()) return b;

    if (a.fileIndex() != b.fileIndex()) return a;

    if (b.isFile()) return a;
    if (a.isFile()) return b;

    if (a.line() == b.line()) return a.column() < b.column() ? a : b;
    return a.line() < b.line() ? a : b;
}

std::ostream& ance::core::operator<<(std::ostream& os, Location const& location)
{
    if (!location.isGlobal() && !location.isFile())
    {
        os << "(" << location.start_line_ << ":" << location.start_column_ << ")";
    }
    else
    {
        os << "()";
    }

    return os;
}
