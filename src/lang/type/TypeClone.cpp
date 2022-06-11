#include "TypeClone.h"

#include "lang/scope/Scope.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeClone::TypeClone(const std::string&                name,
                           lang::ResolvingHandle<lang::Type> original,
                           lang::Location                    definition_location,
                           lang::Location                    original_type_location)
    : lang::TypeDefinition(name, definition_location)
    , original_(original)
    , original_type_location_(original_type_location)
{}

StateCount lang::TypeClone::getStateCount() const
{
    return original_->getStateCount();
}

bool lang::TypeClone::isIntegerType() const
{
    return original_->isIntegerType();
}

bool lang::TypeClone::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    return original_->isIntegerType(bit_size, is_signed);
}

bool lang::TypeClone::isBooleanType() const
{
    return original_->isBooleanType();
}

bool lang::TypeClone::isFloatingPointType() const
{
    return original_->isFloatingPointType();
}

bool lang::TypeClone::isFloatingPointType(size_t precision) const
{
    return original_->isFloatingPointType(precision);
}

bool lang::TypeClone::isSizeType() const
{
    return original_->isSizeType();
}

bool lang::TypeClone::isDiffType() const
{
    return original_->isDiffType();
}

bool lang::TypeClone::isVoidType() const
{
    return original_->isVoidType();
}

bool lang::TypeClone::isPointerType() const
{
    return original_->isPointerType();
}

bool lang::TypeClone::isReferenceType() const
{
    return original_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getElementType() const
{
    return original_->getElementType();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getOriginalType() const
{
    return original_;
}

void lang::TypeClone::onScope()
{
    scope()->addType(original_);
}

llvm::Constant* lang::TypeClone::getDefaultContent(llvm::LLVMContext& c)
{
    return original_->getDefaultContent(c);
}

llvm::Type* lang::TypeClone::getContentType(llvm::LLVMContext& c)
{
    return original_->getContentType(c);
}

bool lang::TypeClone::isSubscriptDefined()
{
    return original_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getSubscriptReturnType()
{
    return original_->getSubscriptReturnType();
}

bool lang::TypeClone::validateDefinition(ValidationLogger& validation_logger)
{
    if (is_valid_) return is_valid_.value();

    bool valid = true;

    if (!original_->isDefined())
    {
        validation_logger.logError("Cannot clone undefined type " + original_->getAnnotatedName(),
                                   original_type_location_);
        valid = false;
    }

    if (original_->getDefinition() == this)
    {
        validation_logger.logError("Cannot clone self", original_type_location_);
        valid = false;
    }

    if (original_ == lang::VoidType::get())// Prevent infinite recursion.
    {
        validation_logger.logError("Cannot create clone of 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid = valid && checkDependencies(validation_logger);

    if (valid)// These checks depend on the definition being roughly valid.
    {
        if (original_
                ->isReferenceType())// Could currently cause problems, as conversion requires actual reference type.
        {
            validation_logger.logError("Cannot clone reference type " + original_->getAnnotatedName(),
                                       original_type_location_);
            valid = false;
        }

        valid &= original_->validate(validation_logger, original_type_location_);
    }

    is_valid_ = valid;
    return is_valid_.value();
}

bool lang::TypeClone::validate(ValidationLogger& validation_logger, lang::Location)
{
    return validateDefinition(validation_logger);
}

bool lang::TypeClone::validateSubscript(lang::Location                    indexed_location,
                                        lang::ResolvingHandle<lang::Type> index_type,
                                        lang::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return original_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeClone::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    return original_->buildSubscript(indexed, index, context);
}

llvm::DIType* lang::TypeClone::createDebugType(CompileContext* context)
{
    return original_->getDebugType(context);
}

std::vector<lang::TypeDefinition*> lang::TypeClone::getDependencies()
{
    std::vector<lang::TypeDefinition*> dependencies;
    if (original_->isDefined()) dependencies.push_back(original_->getDefinition());

    return dependencies;
}
std::string lang::TypeClone::createMangledName()
{
    return getName();
}
