#include "ArrayType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::ArrayType::ArrayType(lang::ResolvingHandle<lang::Type> element_type, const uint64_t size)
    : TypeDefinition(lang::Identifier::from("[" + element_type->name() + "; " + std::to_string(size) + "]"))
    , SequenceType(element_type, size)
{}

bool lang::ArrayType::isArrayType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else { return lang::ArrayType::get(actual_element_type, size_.value()); }
}

llvm::Constant* lang::ArrayType::getDefaultContent(llvm::Module& m)
{
    std::vector<llvm::Constant*> content(size_.value(), element_type_->getDefaultContent(m));
    return llvm::ConstantArray::get(getContentType(m.getContext()), content);
}

llvm::ArrayType* lang::ArrayType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::ArrayType::get(element_type_->getContentType(c), size_.value());
}

bool lang::ArrayType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (size_ > MAX_ARRAY_TYPE_SIZE)
    {
        validation_logger.logError("Array type size cannot be larger than " + std::to_string(MAX_ARRAY_TYPE_SIZE),
                                   location);
        return false;
    }

    if (lang::validation::isTypeUndefined(element_type_, element_type_->name().location(), validation_logger))
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

llvm::DIType* lang::ArrayType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl         = context.module()->getDataLayout();
    llvm::Type*             array_type = getContentType(*context.llvmContext());

    uint64_t      size            = dl.getTypeSizeInBits(array_type);
    auto          alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(array_type));
    llvm::DIType* element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context.di()->getOrCreateSubrange(0, static_cast<int64_t>(size_.value())));

    return context.di()->createArrayType(size, alignment, element_di_type, context.di()->getOrCreateArray(subscripts));
}

lang::TypeRegistry<uint64_t>& lang::ArrayType::getArrayTypes()
{
    static lang::TypeRegistry<uint64_t> array_types;
    return array_types;
}

lang::TypeDefinitionRegistry* lang::ArrayType::getRegistry()
{
    return &getArrayTypes();
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
{
    element_type = element_type->toSeparateUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getArrayTypes().get(used_types, size);

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             array_type = new lang::ArrayType(element_type, size);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::ArrayType>(array_type));
        getArrayTypes().add(std::move(used_types), size, type);

        return type;
    }
}

