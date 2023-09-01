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
                                                     lang::GlobalVariable::Initializer init,
                                                     lang::Scope*                      init_scope,
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
                                                                                  init_scope,
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
}

lang::Identifier const& lang::Variable::name() const
{
    return name_;
}

lang::Scope* lang::Variable::scope()
{
    return definition_.hasValue() ? definition_.value()->scope() : nullptr;
}

lang::Scope const* lang::Variable::scope() const
{
    return definition_.hasValue() ? definition_.value()->scope() : nullptr;
}

lang::ResolvingHandle<lang::Type> lang::Variable::type()
{
    return type_;
}

lang::Type const& lang::Variable::type() const
{
    return type_;
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

void lang::Variable::buildInitialization(CompileContext& context)
{
    definition_.value()->buildInitialization(context);
}

void lang::Variable::buildFinalization(CompileContext& context)
{
    definition_.value()->buildFinalization(context);
}

bool lang::Variable::validateGetValue(ValidationLogger&, lang::Location) const
{
    // If the type is undefined, this is not an error with the variable itself, but with the type.
    // It still blocks any further validation, so we return false.

    return type().isDefined();
}

bool lang::Variable::validateSetValue(lang::Value const& value,
                                      ValidationLogger&  validation_logger,
                                      lang::Location     assignable_location,
                                      lang::Location     assigned_location) const
{
    // The following variable methods require that the variable and type is defined.
    if (not type().isDefined()) return false;
    if (not value.type().isDefined()) return false;

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

lang::ResolvingHandle<lang::Entity> lang::Variable::getUndefinedClone(lang::Context&) const
{
    return toUndefined();
}
