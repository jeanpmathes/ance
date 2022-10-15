#include "Variable.h"

#include <utility>
#include <iostream>

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

lang::Variable::Variable(lang::Identifier name) : name_(std::move(name)) {}

bool lang::Variable::isDefined() const
{
    return (definition_ != nullptr);
}

void lang::Variable::defineAsGlobal(lang::ResolvingHandle<lang::Type> type,
                                    lang::Location                    type_location,
                                    GlobalScope&                      containing_scope,
                                    lang::AccessModifier              access,
                                    std::unique_ptr<Expression>       init,
                                    bool                              is_final,
                                    bool                              is_constant,
                                    lang::Location                    location)
{
    definition_ = std::make_unique<lang::GlobalVariable>(self(),
                                                         type,
                                                         type_location,
                                                         containing_scope,
                                                         access,
                                                         std::move(init),
                                                         is_final,
                                                         is_constant,
                                                         location);

    addChild(*definition_);
}

void lang::Variable::defineAsLocal(lang::ResolvingHandle<lang::Type>   type,
                                   lang::Location                      type_location,
                                   Scope&                              containing_scope,
                                   bool                                is_final,
                                   const std::shared_ptr<lang::Value>& value,
                                   unsigned int                        parameter_no,
                                   lang::Location                      location)
{
    definition_ = std::make_unique<lang::LocalVariable>(self(),
                                                        type,
                                                        type_location,
                                                        containing_scope,
                                                        is_final,
                                                        value,
                                                        parameter_no,
                                                        location);

    addChild(*definition_);
}

const lang::Identifier& lang::Variable::name() const
{
    return name_;
}

lang::Scope* lang::Variable::scope() const
{
    assert(definition_);
    return definition_->scope();
}

lang::ResolvingHandle<lang::Type> lang::Variable::type() const
{
    assert(definition_);
    return definition_->type();
}

bool lang::Variable::isFinal() const
{
    assert(definition_);
    return definition_->isFinal();
}

void lang::Variable::validate(ValidationLogger& validation_logger) const
{
    definition_->validate(validation_logger);
}

void lang::Variable::buildDeclaration(CompileContext& context)
{
    definition_->buildDeclaration(context);
}

void lang::Variable::buildDefinition(CompileContext& context)
{
    definition_->buildDefinition(context);
}

void lang::Variable::buildFinalization(CompileContext& context)
{
    definition_->buildFinalization(context);
}

bool lang::Variable::validateGetValue(ValidationLogger& validation_logger, lang::Location location) const
{
    return not lang::validation::isNameUndefined(self(), location, validation_logger) && type()->isDefined();
}

bool lang::Variable::validateSetValue(const std::shared_ptr<lang::Value>& value,
                                      ValidationLogger&                   validation_logger,
                                      lang::Location                      assignable_location,
                                      lang::Location                      assigned_location) const
{
    if (lang::validation::isNameUndefined(self(), assignable_location, validation_logger)) return false;
    // The following variable methods require that the variable is defined.

    if (isFinal())
    {
        validation_logger.logError("Cannot assign to final variable '" + name() + "'", assignable_location);
        return false;// Type mismatch is not relevant if assignment is not allowed no matter what.
    }

    lang::ResolvingHandle<lang::Type> target_type = type();

    if (type()->isReferenceType()) { target_type = type()->getElementType(); }

    return lang::Type::checkMismatch(target_type, value->type(), assigned_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::Variable::getValue(CompileContext& context)
{
    return definition_->getValue(context);
}

void lang::Variable::setValue(std::shared_ptr<Value> value, CompileContext& context)
{
    definition_->setValue(value, context);
}

lang::ResolvingHandle<lang::Variable> lang::Variable::toUndefined() const
{
    return lang::makeHandled<lang::Variable>(name());
}

void lang::Variable::expand()
{
    definition_->expand();
}

void lang::Variable::determineFlow()
{
    definition_->determineFlow();
}

void lang::Variable::validateFlow(ValidationLogger& validation_logger) const
{
    definition_->validateFlow(validation_logger);
}

void lang::Variable::resolve()
{
    definition_->resolve();
}

void lang::Variable::postResolve()
{
    definition_->postResolve();
}

void lang::Variable::createNativeBacking(CompileContext& context)
{
    definition_->createNativeBacking(context);
}

void lang::Variable::build(CompileContext& context)
{
    definition_->build(context);
}

std::set<lang::ResolvingHandle<lang::Variable>> lang::Variable::getVariableDependencies() const
{
    return definition_->getVariableDependencies();
}

std::set<lang::ResolvingHandle<lang::Function>> lang::Variable::getFunctionDependencies() const
{
    return definition_->getFunctionDependencies();
}
