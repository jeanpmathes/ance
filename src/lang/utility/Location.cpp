#include "Location.h"

#include <iostream>

#include <llvm/IR/DIBuilder.h>

lang::Location::Location(unsigned int start_line,
                         unsigned int start_column,
                         unsigned int end_line,
                         unsigned int end_column)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
{}

unsigned lang::Location::line() const
{
    return start_line_;
}

unsigned lang::Location::column() const
{
    return start_column_;
}

unsigned lang::Location::columnEnd() const
{
    return end_column_;
}

bool lang::Location::isGlobal() const
{
    return start_line_ == 0;
}

bool lang::Location::isSingleLine() const
{
    return start_line_ == end_line_;
}

llvm::DebugLoc lang::Location::getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope) const
{
    return llvm::DILocation::get(*llvm_context, line(), column(), scope);
}

void lang::Location::extend(lang::Location location)
{
    start_line_   = std::min(start_line_, location.start_line_);
    start_column_ = std::min(start_column_, location.start_column_);

    end_line_   = std::max(end_line_, location.end_line_);
    end_column_ = std::max(end_column_, location.end_column_);
}

std::ostream& lang::operator<<(std::ostream& os, const lang::Location& location)
{
    if (!location.isGlobal()) { os << "(" << location.start_line_ << ", " << location.start_column_ << ")"; }
    else {
        os << "()";
    }

    return os;
}
