#include "ArrayType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::ArrayType::ArrayType(lang::ResolvingHandle<lang::Type> element_type, const uint64_t size)
    : TypeDefinition(lang::Identifier::like("[" + element_type->name() + "; " + std::to_string(size) + "]"))
    , SequenceType(element_type, size)
{}

lang::ArrayType const* lang::ArrayType::isArrayType() const
{
    return this;
}

lang::ArrayType* lang::ArrayType::isArrayType()
{
    return this;
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::getActualType()
{
    if (!actual_type_.hasValue())
    {
        lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
        if (actual_element_type == element_type_) { actual_type_ = self(); }
        else { actual_type_ = scope()->context().getArrayType(actual_element_type, size_.value()); }
    }

    return actual_type_.value();
}

lang::Type const& lang::ArrayType::getActualType() const
{
    const_cast<ArrayType*>(this)->getActualType();
    return actual_type_.value();
}

llvm::Constant* lang::ArrayType::getDefaultContent(llvm::Module& m) const
{
    std::vector<llvm::Constant*> const content(size_.value(), element_type_->getDefaultContent(m));
    return llvm::ConstantArray::get(getContentType(m.getContext()), content);
}

llvm::ArrayType* lang::ArrayType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::ArrayType::get(element_type_->getContentType(c), size_.value());
}

bool lang::ArrayType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (size_.value() > MAX_ARRAY_TYPE_SIZE)
    {
        validation_logger.logError("Array type size cannot be larger than " + std::to_string(MAX_ARRAY_TYPE_SIZE),
                                   location);
        return false;
    }

    if (lang::validation::isTypeUndefined(element_type_, scope(), element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare arrays of reference types", location);
        return false;
    }

    return true;
}

std::string lang::ArrayType::createMangledName() const
{
    return std::string("(") + element_type_->getMangledName() + ")x(" + std::to_string(size_.value())
         + std::string(")");
}

llvm::DIType* lang::ArrayType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl         = context.llvmModule().getDataLayout();
    llvm::Type*             array_type = getContentType(context.llvmContext());

    uint64_t const size            = dl.getTypeSizeInBits(array_type);
    auto           alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(array_type));
    llvm::DIType*  element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context.di().getOrCreateSubrange(0, static_cast<int64_t>(size_.value())));

    return context.di().createArrayType(size, alignment, element_di_type, context.di().getOrCreateArray(subscripts));
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::clone(lang::Context& new_context) const
{
    return new_context.getArrayType(element_type_->getUndefinedTypeClone(new_context), size_.value());
}
