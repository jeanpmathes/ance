#include "BufferType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/SizeType.h"
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
        else { actual_type_ = scope()->context().getBufferType(actual_element_type); }
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
    if (lang::Type::isTypeUndefined(element_type_, scope(), element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare buffer pointers to reference types", location);
        return false;
    }

    return true;
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

Execution::Type lang::BufferType::createDebugType(CompileContext& context) const
{
    return context.exec().registerAddressType(self());
}

Execution::IndexingMode lang::BufferType::getIndexingMode() const
{
    return Execution::IndexingMode::POINTER;
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::BufferType::getDeclarationDependencies()
{
    return {};// A pointer does not depend on the pointee type.
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::BufferType::getDefinitionDependencies()
{
    std::vector<ResolvingHandle<Type>> dependencies;
    dependencies.emplace_back(element_type_);
    return dependencies;
}

Optional<lang::ResolvingHandle<lang::Type>> lang::BufferType::getPointeeType()
{
    return element_type_;
}

lang::Type const* lang::BufferType::getPointeeType() const
{
    return &*element_type_;
}

lang::ResolvingHandle<lang::Type> lang::BufferType::clone(lang::Context& new_context) const
{
    return new_context.getBufferType(element_type_->getUndefinedTypeClone(new_context));
}
