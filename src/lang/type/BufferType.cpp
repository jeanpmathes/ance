#include "BufferType.h"

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

lang::BufferType::BufferType(lang::ResolvingHandle<lang::Type> element_type)
    : TypeDefinition(lang::Identifier::like("[]" + element_type->name()))
    , SequenceType(element_type, std::nullopt)
    , IndirectType(element_type)
{}

StateCount lang::BufferType::getStateCount() const
{
    return AddressType::getStateCount();
}

bool lang::BufferType::isBufferType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::BufferType::getActualType()
{
    if (!actual_type_.hasValue())
    {
        lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
        if (actual_element_type == element_type_) { actual_type_ = self(); }
        else { actual_type_ = lang::BufferType::get(actual_element_type); }
    }

    return actual_type_.value();
}

lang::Type const& lang::BufferType::getActualType() const
{
    const_cast<BufferType*>(this)->getActualType();
    return actual_type_.value();
}

bool lang::BufferType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (lang::validation::isTypeUndefined(element_type_, element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare buffer pointers to reference types", location);
        return false;
    }

    return true;
}

llvm::Type* lang::BufferType::getIndexedType(CompileContext& context) const
{
    return element_type_->getContentType(*context.llvmContext());
}

llvm::Value* lang::BufferType::getIndexingPointer(Shared<Value> indexed, CompileContext& context)
{
    indexed->buildContentValue(context);
    return indexed->getContentValue();
}

llvm::SmallVector<llvm::Value*> lang::BufferType::getNativeIndices(llvm::Value*, llvm::Value* index)
{
    return {index};
}

bool lang::BufferType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::BufferType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::BufferType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::BufferType::createMangledName() const
{
    return std::string("ptr_b") + "(" + element_type_->getMangledName() + ")";
}

llvm::DIType* lang::BufferType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.module()->getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));

    llvm::DIType* di_type;

    if (element_type_->isVoidType())
    {
        std::string const name     = std::string(this->name().text());
        auto              encoding = llvm::dwarf::DW_ATE_address;

        di_type = context.di()->createBasicType(name, size_in_bits, encoding);
    }
    else
    {
        llvm::DIType* element_di_type = element_type_->getDebugType(context);

        di_type = context.di()->createPointerType(element_di_type, size_in_bits);
    }

    return di_type;
}

std::vector<lang::TypeDefinition const*> lang::BufferType::getDependencies() const
{
    return {};// A pointer does not depend on the pointee type.
}

std::vector<std::reference_wrapper<const lang::Type>> lang::BufferType::getContained() const
{
    return {element_type_};
}

lang::TypeRegistry<>& lang::BufferType::getBufferTypes()
{
    static TypeRegistry<> buffer_types;
    return buffer_types;
}

lang::TypeDefinitionRegistry* lang::BufferType::getRegistry()
{
    return &getBufferTypes();
}

lang::ResolvingHandle<lang::Type> lang::BufferType::get(lang::ResolvingHandle<lang::Type> element_type)
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = getBufferTypes().get(used_types, lang::Empty());

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             buffer_type = *(new lang::BufferType(element_type));
        lang::ResolvingHandle<lang::Type> type = lang::makeHandled<lang::Type>(Owned<lang::BufferType>(buffer_type));
        getBufferTypes().add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}

Optional<lang::ResolvingHandle<lang::Type>> lang::BufferType::getPointeeType()
{
    return element_type_;
}

lang::Type const* lang::BufferType::getPointeeType() const
{
    return &*element_type_;
}

lang::ResolvingHandle<lang::Type> lang::BufferType::clone() const
{
    return lang::BufferType::get(const_cast<lang::BufferType*>(this)->element_type_->createUndefinedClone());
}
