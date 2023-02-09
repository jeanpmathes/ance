#include "Location.h"

#include <iostream>

#include <llvm/IR/DIBuilder.h>

#include "compiler/CompileContext.h"

lang::Location::Location(size_t start_line, size_t start_column, size_t end_line, size_t end_column, size_t file_index)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
    , file_index_(file_index)
{}

lang::Location lang::Location::global()
{
    return {0, 0, 0, 0, 0};
}

size_t lang::Location::line() const
{
    return start_line_;
}

size_t lang::Location::column() const
{
    return start_column_;
}

size_t lang::Location::columnEnd() const
{
    return end_column_;
}

size_t lang::Location::file() const
{
    return file_index_;
}

bool lang::Location::isGlobal() const
{
    return start_line_ == 0;
}

bool lang::Location::isSingleLine() const
{
    return start_line_ == end_line_;
}

llvm::DebugLoc lang::Location::getDebugLoc(llvm::LLVMContext& llvm_context, llvm::DIScope* scope) const
{
    return llvm::DILocation::get(llvm_context, static_cast<unsigned>(line()), static_cast<unsigned>(column()), scope);
}

void lang::Location::extend(lang::Location location)
{
    assert(location.file() == file());

    if (this->isGlobal()) { *this = location; }
    else if (location.isGlobal()) { return; }

    start_line_   = std::min(start_line_, location.start_line_);
    start_column_ = std::min(start_column_, location.start_column_);

    end_line_   = std::max(end_line_, location.end_line_);
    end_column_ = std::max(end_column_, location.end_column_);
}

std::string lang::Location::toString(CompileContext& context)
{
    if (isGlobal()) return "<internal>";

    return context.getSourceFilePath(*this).generic_string() + ":" + std::to_string(line()) + ":"
         + std::to_string(column());
}

std::ostream& lang::operator<<(std::ostream& os, lang::Location const& location)
{
    if (!location.isGlobal()) { os << "(" << location.start_line_ << ", " << location.start_column_ << ")"; }
    else { os << "()"; }

    return os;
}
