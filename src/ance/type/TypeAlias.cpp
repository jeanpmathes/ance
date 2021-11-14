#include "TypeAlias.h"

#include "ance/type/Type.h"

ance::TypeAlias::TypeAlias(const std::string& identifier, ance::ResolvingHandle<ance::Type> actual)
    : ance::TypeDefinition(identifier)
    , actual_(actual)
{}

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

bool ance::TypeAlias::validate(ValidationLogger& validation_logger, ance::Location location)
{
    return actual_->validate(validation_logger, location);
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

llvm::DIType* ance::TypeAlias::createDebugType(CompileContext* context)
{
    return actual_->getDebugType(context);
}
