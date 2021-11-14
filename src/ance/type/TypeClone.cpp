#include "TypeClone.h"

#include "ance/type/Type.h"

ance::TypeClone::TypeClone(const std::string& identifier, ance::ResolvingHandle<ance::Type> original)
    : ance::TypeDefinition(identifier)
    , original_(original)
{}

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

bool ance::TypeClone::validate(ValidationLogger& validation_logger, ance::Location location)
{
    return original_->validate(validation_logger, location);
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
