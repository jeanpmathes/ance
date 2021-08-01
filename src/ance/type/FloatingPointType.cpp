#include "FloatingPointType.h"

#include "compiler/CompileContext.h"

llvm::DIType* ance::FloatingPointType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name = getName();
    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto encoding = llvm::dwarf::DW_ATE_float;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}
