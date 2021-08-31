#include "Location.h"

#include <iostream>

#include <llvm/IR/DIBuilder.h>

ance::Location::Location(unsigned int start_line,
                         unsigned int start_column,
                         unsigned int end_line,
                         unsigned int end_column)
    : start_line_(start_line)
    , start_column_(start_column)
    , end_line_(end_line)
    , end_column_(end_column)
{}

unsigned ance::Location::line() const
{
    return start_line_;
}

unsigned ance::Location::column() const
{
    return start_column_;
}

llvm::DebugLoc ance::Location::getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope) const
{
    return llvm::DILocation::get(*llvm_context, line(), column(), scope);
}

std::ostream& ance::operator<<(std::ostream& os, const ance::Location& location)
{
    if (location.start_line_ != 0) { os << "(" << location.start_line_ << ", " << location.start_column_ << ")"; }
    else// Line numbers begin with 1 so this location refers to no place.
    {
        os << "()";
    }

    return os;
}
