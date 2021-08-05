#include "Location.h"

#include "llvm/IR/DIBuilder.h"

ance::Location::Location(unsigned int line, unsigned int column) : line_(line), column_(column) {}

unsigned ance::Location::line() const
{
    return line_;
}

unsigned ance::Location::column() const
{
    return column_;
}

llvm::DebugLoc ance::Location::getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope)
{
    return llvm::DILocation::get(*llvm_context, line_, column_, scope);
}
