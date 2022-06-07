#include "TypeAlias.h"

#include "lang/scope/Scope.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeAlias::TypeAlias(const std::string&                identifier,
                           lang::ResolvingHandle<lang::Type> actual,
                           lang::Location                    definition_location,
                           lang::Location                    actual_type_location)
    : lang::TypeDefinition(identifier, definition_location)
    , actual_(actual)
    , actual_type_location_(actual_type_location)
{}

StateCount lang::TypeAlias::getStateCount() const
{
    return actual_->getStateCount();
}

bool lang::TypeAlias::isIntegerType() const
{
    return actual_->isIntegerType();
}

bool lang::TypeAlias::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    return actual_->isIntegerType(bit_size, is_signed);
}

bool lang::TypeAlias::isBooleanType() const
{
    return actual_->isBooleanType();
}

bool lang::TypeAlias::isFloatingPointType() const
{
    return actual_->isFloatingPointType();
}

bool lang::TypeAlias::isFloatingPointType(size_t precision) const
{
    return actual_->isFloatingPointType(precision);
}

bool lang::TypeAlias::isSizeType() const
{
    return actual_->isSizeType();
}

bool lang::TypeAlias::isDiffType() const
{
    return actual_->isDiffType();
}

bool lang::TypeAlias::isVoidType() const
{
    return actual_->isVoidType();
}

bool lang::TypeAlias::isPointerType() const
{
    return actual_->isPointerType();
}

bool lang::TypeAlias::isReferenceType() const
{
    return actual_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getElementType() const
{
    return actual_->getElementType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getActualType() const
{
    if (!actually_actual_.has_value())
    {
        lang::ResolvingHandle<lang::Type> current = actual_;

        while (current != current->getActualType()) { current = current->getActualType(); }

        actually_actual_.emplace(current);
    }

    return actually_actual_.value();
}

void lang::TypeAlias::onScope()
{
    scope()->addType(actual_);
}

llvm::Constant* lang::TypeAlias::getDefaultContent(llvm::LLVMContext& c)
{
    return actual_->getDefaultContent(c);
}

llvm::Type* lang::TypeAlias::getContentType(llvm::LLVMContext& c)
{
    return actual_->getContentType(c);
}

bool lang::TypeAlias::isSubscriptDefined()
{
    return actual_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getSubscriptReturnType()
{
    return actual_->getSubscriptReturnType();
}

bool lang::TypeAlias::validateDefinition(ValidationLogger& validation_logger)
{
    if (is_valid_) return is_valid_.value();

    bool valid = true;

    if (actual_->getDefinition() == this)
    {
        validation_logger.logError("Cannot alias self", actual_type_location_);
        valid = false;
    }

    if (!actual_->isDefined())
    {
        validation_logger.logError("Cannot alias undefined type " + actual_->getAnnotatedName(), actual_type_location_);
        valid = false;
    }

    if (actual_ == lang::VoidType::get())// Prevent infinite recursion.
    {
        validation_logger.logError("Cannot create alias for 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid = valid && checkDependencies(validation_logger);

    is_valid_ = valid && actual_->validate(validation_logger, actual_type_location_);
    return is_valid_.value();
}

bool lang::TypeAlias::validate(ValidationLogger& validation_logger, lang::Location)
{
    return validateDefinition(validation_logger);
}

bool lang::TypeAlias::validateSubscript(lang::Location                    indexed_location,
                                        lang::ResolvingHandle<lang::Type> index_type,
                                        lang::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return actual_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    return actual_->buildSubscript(indexed, index, context);
}

std::string lang::TypeAlias::createMangledName()
{
    return getActualType()->getMangledName();
}

llvm::DIType* lang::TypeAlias::createDebugType(CompileContext* context)
{
    return actual_->getDebugType(context);
}

std::vector<lang::TypeDefinition*> lang::TypeAlias::getDependencies()
{
    std::vector<lang::TypeDefinition*> dependencies;
    if (actual_->isDefined()) dependencies.push_back(actual_->getDefinition());

    return dependencies;
}
