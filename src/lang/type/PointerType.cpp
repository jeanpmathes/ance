#include "PointerType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::PointerType::PointerType(lang::ResolvingHandle<lang::Type> element_type)
    : TypeDefinition(lang::Identifier::from("*" + element_type->name()))
    , SequenceType(element_type, std::nullopt)
    , IndirectType(element_type)
{}

StateCount lang::PointerType::getStateCount() const
{
    return AddressType::getStateCount();
}

bool lang::PointerType::isPointerType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::PointerType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else { return lang::PointerType::get(actual_element_type); }
}

bool lang::PointerType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (lang::validation::isTypeUndefined(element_type_, element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare pointers to reference types", location);
        return false;
    }

    if (element_type_->isVoidType())
    {
        validation_logger.logError("Cannot declare pointers to void type", location);
        return false;
    }

    return true;
}

llvm::Type* lang::PointerType::getIndexedType(CompileContext& context) const
{
    return element_type_->getContentType(*context.llvmContext());
}

llvm::Value* lang::PointerType::getIndexingPointer(std::shared_ptr<Value> indexed, CompileContext& context)
{
    indexed->buildContentValue(context);
    return indexed->getContentValue();
}

llvm::SmallVector<llvm::Value*> lang::PointerType::getNativeIndices(llvm::Value*, llvm::Value* index)
{
    return {index};
}

bool lang::PointerType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::PointerType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::PointerType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::PointerType::createMangledName() const
{
    return std::string("p") + "(" + element_type_->getMangledName() + ")";
}

llvm::DIType* lang::PointerType::createDebugType(CompileContext& context)
{
    llvm::DataLayout const& dl = context.module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));

    llvm::DIType* element_di_type = element_type_->getDebugType(context);
    llvm::DIType* di_type         = context.di()->createPointerType(element_di_type, size_in_bits);

    return di_type;
}

std::vector<lang::TypeDefinition*> lang::PointerType::getDependencies() const
{
    return {};// A pointer does not depend on the pointee type.
}

lang::TypeRegistry<>& lang::PointerType::getPointerTypes()
{
    static TypeRegistry<> pointer_types;
    return pointer_types;
}

lang::TypeDefinitionRegistry* lang::PointerType::getRegistry()
{
    return &getPointerTypes();
}

lang::ResolvingHandle<lang::Type> lang::PointerType::get(lang::ResolvingHandle<lang::Type> element_type)
{
    element_type = element_type->toSeparateUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getPointerTypes().get(used_types, lang::Empty());

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             pointer_type = new lang::PointerType(element_type);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::PointerType>(pointer_type));
        getPointerTypes().add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}

std::optional<lang::ResolvingHandle<lang::Type>> lang::PointerType::getPointeeType() const
{
    return element_type_;
}
