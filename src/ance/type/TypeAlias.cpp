#include "TypeAlias.h"

#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/scope/Scope.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

ance::TypeAlias::TypeAlias(const std::string&                identifier,
                           ance::ResolvingHandle<ance::Type> actual,
                           ance::Location                    definition_location,
                           ance::Location                    actual_type_location)
    : ance::TypeDefinition(identifier, definition_location)
    , actual_(actual)
    , actual_type_location_(actual_type_location)
{}

ance::ResolvingHandle<ance::Type> ance::TypeAlias::getActualType()
{
    if (!actually_actual_.has_value())
    {
        ance::ResolvingHandle<ance::Type> current = actual_;

        while (current != current->getActualType()) { current = current->getActualType(); }

        actually_actual_.emplace(current);
    }

    return actually_actual_.value();
}

void ance::TypeAlias::onScope()
{
    scope()->addType(actual_);
}

llvm::Constant* ance::TypeAlias::getDefaultContent(llvm::LLVMContext& c)
{
    return actual_->getDefaultContent(c);
}

llvm::Type* ance::TypeAlias::getContentType(llvm::LLVMContext& c)
{
    return actual_->getContentType(c);
}

bool ance::TypeAlias::isSubscriptDefined()
{
    return actual_->isSubscriptDefined();
}

ance::ResolvingHandle<ance::Type> ance::TypeAlias::getSubscriptReturnType()
{
    return actual_->getSubscriptReturnType();
}

bool ance::TypeAlias::validateDefinition(ValidationLogger& validation_logger)
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
        validation_logger.logError("Cannot alias undefined type '" + actual_->getName() + "'", actual_type_location_);
        valid = false;
    }

    if (actual_ == ance::VoidType::get())
    {
        validation_logger.logError("Cannot create alias for 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid = valid && checkDependencies(validation_logger);

    is_valid_ = valid && actual_->validate(validation_logger, actual_type_location_);
    return is_valid_.value();
}

bool ance::TypeAlias::validate(ValidationLogger& validation_logger, ance::Location)
{
    return validateDefinition(validation_logger);
}

bool ance::TypeAlias::validateSubscript(ance::Location                    indexed_location,
                                        ance::ResolvingHandle<ance::Type> index_type,
                                        ance::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return actual_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::TypeAlias::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    return actual_->buildSubscript(indexed, index, context);
}

bool ance::TypeAlias::isImplicitlyConvertibleTo(ance::ResolvingHandle<ance::Type> target)
{
    if (target == actual_) return true;

    return actual_->isImplicitlyConvertibleTo(target);
}

std::shared_ptr<ance::Value> ance::TypeAlias::convertImplicitlyTo(ance::ResolvingHandle<ance::Type> target,
                                                                  std::shared_ptr<Value>            value,
                                                                  CompileContext*                   context)
{
    std::shared_ptr<ance::Value> as_actual = std::make_shared<ance::RoughlyCastedValue>(actual_, value);
    if (target == actual_) return as_actual;

    return actual_->convertImplicitlyTo(target, as_actual, context);
}

bool ance::TypeAlias::isImplicitlyConvertibleFrom(ance::ResolvingHandle<ance::Type> source)
{
    if (source == actual_) return true;

    return actual_->isImplicitlyConvertibleFrom(source);
}

std::shared_ptr<ance::Value> ance::TypeAlias::convertImplicitlyFrom(std::shared_ptr<Value>            value,
                                                                    ance::ResolvingHandle<ance::Type> self,
                                                                    CompileContext*                   context)
{
    std::shared_ptr<ance::Value> as_actual;

    if (value->type() == actual_) { as_actual = value; }
    else
    {
        as_actual = actual_->convertImplicitlyFrom(value, actual_, context);
    }

    return std::make_shared<ance::RoughlyCastedValue>(self, as_actual);
}

llvm::DIType* ance::TypeAlias::createDebugType(CompileContext* context)
{
    return actual_->getDebugType(context);
}

std::vector<ance::TypeDefinition*> ance::TypeAlias::getDependencies()
{
    std::vector<ance::TypeDefinition*> dependencies;
    if (actual_->isDefined()) dependencies.push_back(actual_->getDefinition());

    return dependencies;
}
