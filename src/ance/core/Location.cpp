#include "Location.h"

#include <cassert>
#include <iostream>

ance::core::Location::Location(size_t start_line, size_t start_column, size_t end_line, size_t end_column, size_t file_index)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
    , file_index_(file_index)
{}

ance::core::Location ance::core::Location::global()
{
    return {0, 0, 0, 0, 0};
}

ance::core::Location ance::core::Location::simple(size_t line, size_t column, size_t file_index)
{
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

size_t ance::core::Location::file() const
{
    return file_index_;
}

bool ance::core::Location::isGlobal() const
{
    return start_line_ == 0;
}

bool ance::core::Location::isSingleLine() const
{
    return start_line_ == end_line_;
}

void ance::core::Location::extend(Location const& location)
{
    if (this->isGlobal())
    {
        *this = location;
        return;
    }
    else if (location.isGlobal()) { return; }

    assert(location.file() == file());

    start_line_   = std::min(start_line_, location.start_line_);
    start_column_ = std::min(start_column_, location.start_column_);

    end_line_   = std::max(end_line_, location.end_line_);
    end_column_ = std::max(end_column_, location.end_column_);
}

ance::core::Location ance::core::Location::getFirst(Location a, Location b)
{
    if (b.isGlobal()) return a;
    if (a.isGlobal()) return b;

    if (a.file() != b.file()) return a;

    if (a.line() == b.line()) return a.column() < b.column() ? a : b;
    return a.line() < b.line() ? a : b;
}

std::ostream& ance::core::operator<<(std::ostream& os, Location const& location)
{
    if (!location.isGlobal()) { os << "(" << location.start_line_ << ":" << location.start_column_ << ")"; }
    else { os << "()"; }

    return os;
}
