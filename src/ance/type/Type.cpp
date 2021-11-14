#include "Type.h"

#include "ance/construct/value/Value.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

ance::Type::Type(std::string name) : name_(std::move(name)) {}

ance::Type::Type(std::unique_ptr<ance::TypeDefinition> definition)
    : name_(definition->getName())
    , definition_(std::move(definition))
{}

const std::string& ance::Type::getName() const
{
    if (isDefined()) { return definition_->getName(); }
    else
    {
        return name_;
    }
}

bool ance::Type::isDefined() const
{
    return (definition_ != nullptr);
}

void ance::Type::define(std::unique_ptr<ance::TypeDefinition> definition)
{
    assert(!isDefined());
    definition_ = std::move(definition);
}

llvm::Constant* ance::Type::getDefaultContent(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getDefaultContent(c);
}

llvm::Type* ance::Type::getNativeType(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getNativeType(c);
}

llvm::Type* ance::Type::getContentType(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getContentType(c);
}

llvm::DIType* ance::Type::getDebugType(CompileContext* context)
{
    assert(isDefined());
    return definition_->getDebugType(context);
}

llvm::TypeSize ance::Type::getNativeSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getNativeSize(m);
}

llvm::TypeSize ance::Type::getContentSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getContentSize(m);
}

bool ance::Type::isSubscriptDefined()
{
    assert(isDefined());
    return definition_->isSubscriptDefined();
}

ance::ResolvingHandle<ance::Type> ance::Type::getSubscriptReturnType()
{
    assert(isDefined());
    return definition_->getSubscriptReturnType();
}

bool ance::Type::validate(ValidationLogger& validation_logger, ance::Location location)
{
    assert(isDefined());
    return definition_->validate(validation_logger, location);
}

bool ance::Type::validateSubscript(ance::Location                    indexed_location,
                                   ance::ResolvingHandle<ance::Type> index_type,
                                   ance::Location                    index_location,
                                   ValidationLogger&                 validation_logger)
{
    assert(isDefined());
    return definition_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::Type::buildSubscript(std::shared_ptr<Value> indexed,
                                                        std::shared_ptr<Value> index,
                                                        CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildSubscript(indexed, index, context);
}

ance::TypeDefinition* ance::Type::getDefinition()
{
    return definition_.get();
}

bool ance::Type::checkMismatch(ance::ResolvingHandle<ance::Type> expected,
                               ance::ResolvingHandle<ance::Type> actual,
                               ance::Location                    location,
                               ValidationLogger&                 validation_logger)
{
    if (expected != actual)
    {
        if (ance::ReferenceType::getReferencedType(actual) == expected) return true;

        validation_logger.logError("Cannot implicitly convert '" + actual->getName() + "' to '" + expected->getName()
                                       + "'",
                                   location);

        return false;
    }

    return true;
}

std::shared_ptr<ance::Value> ance::Type::makeMatching(ance::ResolvingHandle<ance::Type> expected,
                                                      std::shared_ptr<ance::Value>      value,
                                                      CompileContext*                   context)
{
    if (value->type() == expected) return value;

    if (ance::ReferenceType::getReferencedType(value->type()) == expected)
    {
        auto reference_type = dynamic_cast<ance::ReferenceType*>(value->type()->definition_.get());
        return reference_type->getReferenced(value, context);
    }

    assert(false && "Cannot make the value matching, was isMismatch checked before?");
    return nullptr;
}
