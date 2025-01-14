#include "ReferenceType.h"

#include "compiler/Application.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
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
        else { actual_type_ = scope().context().getReferenceType(actual_element_type); }
    }

    return actual_type_.value();
}

lang::Type const& lang::ReferenceType::getActualType() const
{
    const_cast<ReferenceType*>(this)->getActualType();
    return actual_type_.value();
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

lang::Type const& lang::ReferenceType::getSubscriptReturnType() const
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

Shared<lang::Value> lang::ReferenceType::execSubscript(Shared<lang::Value> indexed,
                                                       Shared<lang::Value> index,
                                                        Execution&          exec) const
{
    return element_type_->execSubscript(exec.performDereference(indexed), index, exec);
}

bool lang::ReferenceType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    return element_type_->isOperatorDefined(op, other);
}

lang::Type const& lang::ReferenceType::getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const
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

Shared<lang::Value> lang::ReferenceType::execOperator(lang::BinaryOperator op,
                                                      Shared<lang::Value>  left,
                                                       Shared<lang::Value>  right,
                                                       Execution&           exec) const
{
    return element_type_->execOperator(op, exec.performDereference(left), right, exec);
}

bool lang::ReferenceType::isOperatorDefined(lang::UnaryOperator op) const
{
    return element_type_->isOperatorDefined(op);
}

lang::Type const& lang::ReferenceType::getOperatorResultType(lang::UnaryOperator op) const
{
    return element_type_->getOperatorResultType(op);
}

bool lang::ReferenceType::validateOperator(lang::UnaryOperator op,
                                           lang::Location      location,
                                           ValidationLogger&   validation_logger) const
{
    return element_type_->validateOperator(op, location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::execOperator(lang::UnaryOperator op,
                                                      Shared<lang::Value> value,
                                                       Execution&          exec) const
{
    return element_type_->execOperator(op, exec.performDereference(value), exec);
}

bool lang::ReferenceType::hasMember(lang::Identifier const& name) const
{
    return element_type_->hasMember(name);
}

lang::Member& lang::ReferenceType::getMember(lang::Identifier const& name)
{
    return element_type_->getMember(name);
}

lang::Member const& lang::ReferenceType::getMember(lang::Identifier const& name) const
{
    return element_type_->getMember(name);
}

bool lang::ReferenceType::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    return element_type_->validateMemberAccess(name, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::execMemberAccess(Shared<lang::Value>     value,
                                                          lang::Identifier const& name,
                                                           Execution&              exec) const
{
    return element_type_->execMemberAccess(exec.performDereference(value), name, exec);
}

bool lang::ReferenceType::definesIndirection() const
{
    return element_type_->definesIndirection();
}

lang::Type const& lang::ReferenceType::getIndirectionType() const
{
    return element_type_->getIndirectionType();
}

bool lang::ReferenceType::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return element_type_->validateIndirection(location, validation_logger);
}

Shared<lang::Value> lang::ReferenceType::execIndirection(Shared<lang::Value> value, Execution& exec) const
{
    return element_type_->execIndirection(exec.performDereference(value), exec);
}

bool lang::ReferenceType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::ReferenceType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::ReferenceType::isTriviallyDestructible() const
{
    return true;
}

void lang::ReferenceType::createConstructors() {}

void lang::ReferenceType::registerDeclaration(Execution& exec) const
{
    registerExecutionType(exec);
}

void lang::ReferenceType::registerDefinition(Execution&) const {}

std::string lang::ReferenceType::createMangledName() const
{
    return std::string("ref") + "(" + element_type_->getMangledName() + ")";
}

void lang::ReferenceType::registerExecutionType(Execution& exec) const
{
    return exec.registerReferenceType(self());
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
