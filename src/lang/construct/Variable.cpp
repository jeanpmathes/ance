#include "Variable.h"

#include <iostream>
#include <utility>

#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Parameter.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::Variable::Variable(lang::Identifier name) : name_(name), type_(lang::Type::getUndefined()) {}

bool lang::Variable::isDefined() const
{
    return definition_.hasValue();
}

lang::GlobalVariable* lang::Variable::defineAsGlobal(lang::ResolvingHandle<lang::Type> type,
                                                     lang::Location                    type_location,
                                                     Scope&                            containing_scope,
                                                     lang::AccessModifier              access,
                                                     bool                              is_import,
                                                     lang::GlobalInitializer           init,
                                                     lang::Assigner                    assigner,
                                                     bool                              is_constant,
                                                     lang::Location                    location)
{
    Owned<lang::GlobalVariable> global_variable     = makeOwned<lang::GlobalVariable>(self(),
                                                                                  type,
                                                                                  type_location,
                                                                                  containing_scope,
                                                                                  access,
                                                                                  is_import,
                                                                                  std::move(init),
                                                                                  assigner,
                                                                                  is_constant,
                                                                                  location);
    auto*                       global_variable_ptr = &*global_variable;

    definition_ = std::move(global_variable);

    return global_variable_ptr;
}

void lang::Variable::defineAsLocal(lang::ResolvingHandle<lang::Type> type,
                                   lang::Location                    type_location,
                                   Scope&                            containing_scope,
                                   bool                              is_final,
                                   lang::LocalInitializer const&     init,
                                   Optional<size_t> const&           parameter_index,
                                   lang::Location                    location)
{
    definition_ = makeOwned<lang::LocalVariable>(self(),
                                                 type,
                                                 type_location,
                                                 containing_scope,
                                                 is_final,
                                                 init,
                                                 parameter_index,
                                                 location);
}

lang::Identifier const& lang::Variable::name() const
{
    return name_;
}

lang::Scope& lang::Variable::scope()
{
    assert(definition_.hasValue());
    return definition_.value()->scope();
}

lang::Scope const& lang::Variable::scope() const
{
    assert(definition_.hasValue());
    return definition_.value()->scope();
}

lang::ResolvingHandle<lang::Type> lang::Variable::type()
{
    return type_;
}

lang::Type const& lang::Variable::type() const
{
    return type_;
}

lang::Type const& lang::Variable::targetType() const
{
    if (type().isReferenceType()) { return type().getElementType(); }

    return type();
}

bool lang::Variable::isFinal() const
{
    assert(definition_.hasValue());
    return definition_.value()->isFinal();
}

void lang::Variable::buildDeclaration(Execution& exec) const
{
    definition_.value()->buildDeclaration(exec);
}

void lang::Variable::buildInitialization(Execution& exec) const
{
    definition_.value()->buildInitialization(exec);
}

void lang::Variable::buildFinalization(Execution& exec) const
{
    definition_.value()->buildFinalization(exec);
}

bool lang::Variable::validateGetValue(ValidationLogger&, lang::Location) const
{
    // If the type is undefined, this is not an error with the variable itself, but with the type.
    // It still blocks any further validation, so we return false.

    return type().isDefined();
}

bool lang::Variable::validateSetValue(lang::Type const& value_type,
                                      ValidationLogger& validation_logger,
                                      lang::Location    assignable_location,
                                      lang::Location    assigned_location) const
{
    // The following variable methods require that the variable and type is defined.
    if (not type().isDefined()) return false;
    if (not value_type.isDefined()) return false;

    if (isFinal())
    {
        validation_logger.logError("Cannot assign to final variable '" + name() + "'", assignable_location);
        return false;// Type mismatch is not relevant if assignment is not allowed no matter what.
    }

    return lang::Type::checkMismatch(targetType(), value_type, assigned_location, validation_logger);
}

Shared<lang::Value> lang::Variable::getValuePointer(Execution& exec) const
{
    return definition_.value()->getValuePointer(exec);
}

Shared<lang::Value> lang::Variable::getValue(Execution& exec) const
{
    Shared<lang::Value> pointer = getValuePointer(exec);
    return exec.performLoadFromAddress(pointer);
}

lang::ResolvingHandle<lang::Variable> lang::Variable::toUndefined() const
{
    return lang::makeHandled<lang::Variable>(name());
}

lang::ResolvingHandle<lang::Entity> lang::Variable::getUndefinedClone(lang::Context&) const
{
    return toUndefined();
}
