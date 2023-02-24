#include "Variable.h"

#include <iostream>
#include <utility>

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Parameter.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::Variable::Variable(lang::Identifier name) : name_(name) {}

bool lang::Variable::isDefined() const
{
    return definition_.hasValue();
}

void lang::Variable::defineAsGlobal(lang::ResolvingHandle<lang::Type> type,
                                    lang::Location                    type_location,
                                    GlobalScope&                      containing_scope,
                                    lang::AccessModifier              access,
                                    lang::GlobalVariable::Initializer init,
                                    lang::Scope*                      init_scope,
                                    lang::Assigner                    assigner,
                                    bool                              is_constant,
                                    lang::Location                    location)
{
    definition_ = makeOwned<lang::GlobalVariable>(self(),
                                                  type,
                                                  type_location,
                                                  containing_scope,
                                                  access,
                                                  std::move(init),
                                                  init_scope,
                                                  assigner,
                                                  is_constant,
                                                  location);

    addChild(**definition_);
}

void lang::Variable::defineAsLocal(lang::ResolvingHandle<lang::Type> type,
                                   lang::Location                    type_location,
                                   Scope&                            containing_scope,
                                   bool                              is_final,
                                   Optional<Shared<lang::Value>>     value,
                                   unsigned int                      parameter_no,
                                   lang::Location                    location)
{
    definition_ = makeOwned<lang::LocalVariable>(self(),
                                                 type,
                                                 type_location,
                                                 containing_scope,
                                                 is_final,
                                                 value,
                                                 parameter_no,
                                                 location);

    addChild(**definition_);
}

lang::Identifier const& lang::Variable::name() const
{
    return name_;
}

lang::Scope* lang::Variable::scope() const
{
    assert(definition_.hasValue());
    return definition_.value()->scope();
}

lang::ResolvingHandle<lang::Type> lang::Variable::type()
{
    assert(definition_.hasValue());
    return definition_.value()->type();
}

lang::Type const& lang::Variable::type() const
{
    assert(definition_.hasValue());
    return definition_.value()->type();
}

bool lang::Variable::isFinal() const
{
    assert(definition_.hasValue());
    return definition_.value()->isFinal();
}

void lang::Variable::buildDeclaration(CompileContext& context)
{
    definition_.value()->buildDeclaration(context);
}

void lang::Variable::buildDefinition(CompileContext& context)
{
    definition_.value()->buildDefinition(context);
}

void lang::Variable::buildFinalization(CompileContext& context)
{
    definition_.value()->buildFinalization(context);
}

bool lang::Variable::validateGetValue(ValidationLogger& validation_logger, lang::Location location) const
{
    return not lang::validation::isNameUndefined(self(), location, validation_logger) && type().isDefined();
}

bool lang::Variable::validateSetValue(lang::Value const& value,
                                      ValidationLogger&  validation_logger,
                                      lang::Location     assignable_location,
                                      lang::Location     assigned_location) const
{
    if (lang::validation::isNameUndefined(self(), assignable_location, validation_logger)) return false;
    // The following variable methods require that the variable is defined.

    if (isFinal())
    {
        validation_logger.logError("Cannot assign to final variable '" + name() + "'", assignable_location);
        return false;// Type mismatch is not relevant if assignment is not allowed no matter what.
    }

    std::reference_wrapper<lang::Type const> target_type = type();

    if (type().isReferenceType()) { target_type = type().getElementType(); }

    return lang::Type::checkMismatch(target_type, value.type(), assigned_location, validation_logger);
}

Shared<lang::Value> lang::Variable::getValue(CompileContext& context)
{
    return definition_.value()->getValue(context);
}

void lang::Variable::setValue(Shared<Value> value, CompileContext& context)
{
    definition_.value()->setValue(value, context);
}

lang::ResolvingHandle<lang::Variable> lang::Variable::toUndefined() const
{
    return lang::makeHandled<lang::Variable>(name());
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::Variable::getVariableDependencies()
{
    return definition_.value()->getVariableDependencies();
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Variable::getFunctionDependencies()
{
    return definition_.value()->getFunctionDependencies();
}
