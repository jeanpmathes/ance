#include "ReferenceType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "validation/ValidationLogger.h"

lang::ReferenceType::ReferenceType(lang::ResolvingHandle<lang::Type> element_type)
    : TypeDefinition(lang::Identifier::like("&" + element_type->name()))
    , element_type_(element_type)
{}

StateCount lang::ReferenceType::getStateCount() const
{
    return element_type_->getStateCount();
}

bool lang::ReferenceType::isReferenceType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getElementType()
{
    return element_type_;
}

lang::Type const& lang::ReferenceType::getElementType() const
{
    return element_type_;
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getActualType()
{
    if (!actual_type_.hasValue())
    {
        lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
        if (actual_element_type == element_type_) { actual_type_ = self(); }
        else { actual_type_ = scope()->context().getReferenceType(actual_element_type); }
    }

    return actual_type_.value();
}

lang::Type const& lang::ReferenceType::getActualType() const
{
    const_cast<ReferenceType*>(this)->getActualType();
    return actual_type_.value();
}

llvm::Constant* lang::ReferenceType::getDefaultContent(CompileContext& context) const
{
    // A default value for a reference does not make sense, except for zero-sized types.
    // They are not stored anywhere, so we can just return a null pointer.

    assert(element_type_->getStateCount().isUnit());

    return llvm::ConstantPointerNull::get(llvm::PointerType::get(element_type_->getContentType(context), 0));
}

llvm::PointerType* lang::ReferenceType::getContentType(CompileContext& context) const
{
    return llvm::PointerType::get(element_type_->getContentType(context), 0);
}

bool lang::ReferenceType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (lang::Type::isTypeUndefined(element_type_, scope(), element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare reference to reference", location);
        return false;
    }

    return true;
}

bool lang::ReferenceType::isSubscriptDefined() const
{
    return element_type_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getSubscriptReturnType()
{
    return element_type_->getSubscriptReturnType();
}

bool lang::ReferenceType::validateSubscript(lang::Location    indexed_location,
                                            lang::Type const& index_type,
                                            lang::Location    index_location,
                                            ValidationLogger& validation_logger) const
{
    return element_type_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::buildSubscript(Shared<lang::Value> indexed,
                                                        Shared<lang::Value> index,
                                                        CompileContext& context)
{
    return element_type_->buildSubscript(context.exec().performDereference(indexed), index, context);
}

bool lang::ReferenceType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    return element_type_->isOperatorDefined(op, other);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getOperatorResultType(lang::BinaryOperator              op,
                                                                             lang::ResolvingHandle<lang::Type> other)
{
    return element_type_->getOperatorResultType(op, other);
}

bool lang::ReferenceType::validateOperator(lang::BinaryOperator op,
                                           lang::Type const&    other,
                                           lang::Location       left_location,
                                           lang::Location       right_location,
                                           ValidationLogger&    validation_logger) const
{
    return element_type_->validateOperator(op, other, left_location, right_location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::buildOperator(lang::BinaryOperator op,
                                                       Shared<lang::Value>  left,
                                                       Shared<lang::Value>  right,
                                                       CompileContext&      context)
{
    return element_type_->buildOperator(op, context.exec().performDereference(left), right, context);
}

bool lang::ReferenceType::isOperatorDefined(lang::UnaryOperator op) const
{
    return element_type_->isOperatorDefined(op);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getOperatorResultType(lang::UnaryOperator op)
{
    return element_type_->getOperatorResultType(op);
}

bool lang::ReferenceType::validateOperator(lang::UnaryOperator op,
                                           lang::Location      location,
                                           ValidationLogger&   validation_logger) const
{
    return element_type_->validateOperator(op, location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::buildOperator(lang::UnaryOperator op,
                                                       Shared<lang::Value> value,
                                                       CompileContext&     context)
{
    return element_type_->buildOperator(op, context.exec().performDereference(value), context);
}

bool lang::ReferenceType::hasMember(lang::Identifier const& name) const
{
    return element_type_->hasMember(name);
}

lang::Member& lang::ReferenceType::getMember(lang::Identifier const& name)
{
    return element_type_->getMember(name);
}

bool lang::ReferenceType::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    return element_type_->validateMemberAccess(name, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::buildMemberAccess(Shared<lang::Value>     value,
                                                           lang::Identifier const& name,
                                                           CompileContext&         context)
{
    return element_type_->buildMemberAccess(value, name, context);
}

bool lang::ReferenceType::definesIndirection() const
{
    return element_type_->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getIndirectionType()
{
    return element_type_->getIndirectionType();
}

bool lang::ReferenceType::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return element_type_->validateIndirection(location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::buildIndirection(Shared<lang::Value> value, CompileContext& context)
{
    return element_type_->buildIndirection(context.exec().performDereference(value), context);
}

void lang::ReferenceType::performDefaultInitializer(Shared<lang::Value>, Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Reference does not have a default value");
}

void lang::ReferenceType::performCopyInitializer(Shared<lang::Value>, Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Reference does not have a copy value");
}

void lang::ReferenceType::performFinalizer(Shared<lang::Value>, Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Reference does not have a finalizer");
}

void lang::ReferenceType::createConstructors() {}

void lang::ReferenceType::buildNativeDeclaration(CompileContext&) {}

void lang::ReferenceType::buildNativeDefinition(CompileContext&) {}

std::string lang::ReferenceType::createMangledName() const
{
    return std::string("ref") + "(" + element_type_->getMangledName() + ")";
}

Execution::Type lang::ReferenceType::createDebugType(CompileContext& context) const
{
    return context.exec().registerReferenceType(self());
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::ReferenceType::getDeclarationDependencies()
{
    return {};// A reference does not depend on the referenced type.
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::ReferenceType::getDefinitionDependencies()
{
    std::vector<ResolvingHandle<Type>> dependencies;
    dependencies.emplace_back(element_type_);
    return dependencies;
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::clone(lang::Context& new_context) const
{
    return new_context.getReferenceType(element_type_->getUndefinedTypeClone(new_context));
}
