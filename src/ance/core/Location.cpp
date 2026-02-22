#include "Location.h"

#include <cassert>
#include <iostream>

namespace
{
    enum MODE : size_t
    {
        MODE_NOWHERE = 0,
        MODE_PROJECT = 1,
        MODE_FILE   = 2,
        MODE_CORE   = 3,
    };
}

ance::core::Location::Location(size_t const start_line, size_t const start_column, size_t const end_line, size_t const end_column, size_t const file_index)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
    , file_index_(file_index)
{}
ance::core::Location ance::core::Location::nowhere()
{
    return {0, 0, MODE_NOWHERE, 0, 0};
}

ance::core::Location ance::core::Location::project()
{
    return {0, 0, MODE_PROJECT, 0, 0};
}

ance::core::Location ance::core::Location::file(size_t file_index)
{
    return {0, 0, MODE_FILE, 0, file_index};
}

ance::core::Location ance::core::Location::core()
{
    return {0, 0, MODE_CORE, 0, 0};
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

size_t ance::core::Location::lineEnd() const
{
    return end_line_;
}

size_t ance::core::Location::columnEnd() const
{
    return end_column_;
}

size_t ance::core::Location::fileIndex() const
{
    return file_index_;
}

bool ance::core::Location::isNowhere() const
{
    return start_line_ == 0 && end_line_ == MODE_NOWHERE;
}

bool ance::core::Location::isProject() const
{
    return start_line_ == 0 && end_line_ == MODE_PROJECT;
}

bool ance::core::Location::isCore() const
{
    return start_line_ == 0 && end_line_ == MODE_CORE;
}

bool ance::core::Location::isFile() const
{
    return start_line_ == 0 && end_line_ == MODE_FILE;
}

bool ance::core::Location::isSingleLine() const
{
    return start_line_ == end_line_ && !isProject() && !isCore() && !isFile();
}

void ance::core::Location::extend(Location const& location)
{
    if (this->isProject() || this->isCore() || this->isFile())
        return;

    if (location.isProject() || location.isCore())
        return;

    if (location.isFile())
    {
        if (location.fileIndex() == fileIndex())
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
    if (isProject() || isCore() || isFile()) return *this;

    return {start_line_, start_column_, start_line_, start_column_, file_index_};
}

ance::core::Location ance::core::Location::last() const
{
    if (isProject() || isCore() || isFile()) return *this;

    return {end_line_, end_column_, end_line_, end_column_, file_index_};
}

ance::core::Location ance::core::Location::getFirst(Location const& a, Location const& b)
{
    if (b.isProject() || b.isCore()) return a;
    if (a.isProject() || a.isCore()) return b;

    if (a.fileIndex() != b.fileIndex()) return a;

    if (b.isFile()) return a;
    if (a.isFile()) return b;

    if (a.line() == b.line()) return a.column() < b.column() ? a : b;
    return a.line() < b.line() ? a : b;
}

std::ostream& ance::core::operator<<(std::ostream& os, Location const& location)
{
    if (location.isCore())
    {
        os << "(core)";
    }
    else if (!location.isNowhere() && !location.isProject() && !location.isFile())
    {
        os << "(" << location.start_line_ << ":" << location.start_column_ << ")";
    }
    else
    {
        os << "()";
    }

    return os;
}
