#include "TypeClone.h"

#include "ance/scope/Scope.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

ance::TypeClone::TypeClone(const std::string&                identifier,
                           ance::ResolvingHandle<ance::Type> original,
                           ance::Location                    definition_location,
                           ance::Location                    original_type_location)
    : ance::TypeDefinition(identifier, definition_location)
    , original_(original)
    , original_type_location_(original_type_location)
{}

void ance::TypeClone::onScope()
{
    scope()->addType(original_);
}

llvm::Constant* ance::TypeClone::getDefaultContent(llvm::LLVMContext& c)
{
    return original_->getDefaultContent(c);
}

llvm::Type* ance::TypeClone::getContentType(llvm::LLVMContext& c)
{
    return original_->getContentType(c);
}

bool ance::TypeClone::isSubscriptDefined()
{
    return original_->isSubscriptDefined();
}

ance::ResolvingHandle<ance::Type> ance::TypeClone::getSubscriptReturnType()
{
    return original_->getSubscriptReturnType();
}

bool ance::TypeClone::validateDefinition(ValidationLogger& validation_logger)
{
    assert(!is_valid_);

    bool valid = true;

    if (!original_->isDefined())
    {
        validation_logger.logError("Cannot clone undefined type '" + original_->getName() + "'",
                                   original_type_location_);
        valid = false;
    }

    if (original_ == ance::VoidType::get())
    {
        validation_logger.logError("Cannot create clone of 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid &= checkDependencies(validation_logger);

    is_valid_ = valid && original_->validate(validation_logger, original_type_location_);
    return is_valid_.value();
}

bool ance::TypeClone::validate(ValidationLogger&, ance::Location)
{
    assert(is_valid_ && "Validate the type definition before using the type.");
    return is_valid_.value();
}

bool ance::TypeClone::validateSubscript(ance::Location                    indexed_location,
                                        ance::ResolvingHandle<ance::Type> index_type,
                                        ance::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return original_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::TypeClone::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    return original_->buildSubscript(indexed, index, context);
}

llvm::DIType* ance::TypeClone::createDebugType(CompileContext* context)
{
    return original_->getDebugType(context);
}

std::vector<ance::TypeDefinition*> ance::TypeClone::getDependencies()
{
    std::vector<ance::TypeDefinition*> dependencies;
    if (original_->isDefined()) dependencies.push_back(original_->getDefinition());

    return dependencies;
}
