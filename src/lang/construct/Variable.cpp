#include "Variable.h"

#include <utility>

#include "lang/construct/GlobalVariable.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Parameter.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/Type.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/AccessModifier.h"

lang::Variable::Variable(std::string identifier) : identifier_(std::move(identifier)) {}

bool lang::Variable::isDefined() const
{
    return (definition_ != nullptr);
}

void lang::Variable::defineAsGlobal(lang::ResolvingHandle<lang::Type> type,
                                    lang::Location                    type_location,
                                    lang::GlobalScope*                containing_scope,
                                    lang::AccessModifier              access,
                                    ConstantExpression*               constant_init,
                                    bool                              is_final,
                                    bool                              is_constant,
                                    lang::Location                    location)
{
    definition_ = std::make_unique<lang::GlobalVariable>(identifier(),
                                                         type,
                                                         type_location,
                                                         containing_scope,
                                                         access,
                                                         constant_init,
                                                         is_final,
                                                         is_constant,
                                                         location);

    addChild(*definition_);
}

void lang::Variable::defineAsLocal(lang::ResolvingHandle<lang::Type>   type,
                                   lang::Location                      type_location,
                                   lang::LocalScope*                   containing_scope,
                                   bool                                is_final,
                                   const std::shared_ptr<lang::Value>& value,
                                   unsigned int                        parameter_no,
                                   lang::Location                      location)
{
    definition_ = std::make_unique<lang::LocalVariable>(identifier(),
                                                        type,
                                                        type_location,
                                                        containing_scope,
                                                        is_final,
                                                        value,
                                                        parameter_no,
                                                        location);

    addChild(*definition_);
}

const std::string& lang::Variable::identifier() const
{
    return identifier_;
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

void lang::Variable::validate(ValidationLogger& validation_logger)
{
    definition_->validate(validation_logger);
}

void lang::Variable::buildDeclaration(CompileContext* context)
{
    definition_->buildDeclaration(context);
}

void lang::Variable::buildDefinition(CompileContext* context)
{
    definition_->buildDefinition(context);
}

bool lang::Variable::validateGetValue(ValidationLogger& validation_logger, lang::Location location) const
{
    if (!isDefined())
    {
        validation_logger.logError("Name '" + identifier() + "' not defined in the current context", location);
        return false;
    }

    return true;
}

void lang::Variable::validateSetValue(const std::shared_ptr<lang::Value>& value,
                                      ValidationLogger&                   validation_logger,
                                      lang::Location                      assignable_location,
                                      lang::Location                      assigned_location) const
{
    if (!isDefined())
    {
        validation_logger.logError("Name '" + identifier() + "' not defined in the current context",
                                   assignable_location);
        return;// The following variable methods require that the variable is defined.
    }

    if (isFinal())
    {
        validation_logger.logError("Cannot assign to final variable '" + identifier() + "'", assignable_location);
        return;// Type mismatch is not relevant if assignment is not allowed no matter what.
    }

    lang::ResolvingHandle<lang::Type> target_type = type();

    if (type()->isReferenceType()) { target_type = type()->getElementType(); }

    lang::Type::checkMismatch(target_type, value->type(), assigned_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::Variable::getValue(CompileContext* context)
{
    return definition_->getValue(context);
}

void lang::Variable::setValue(const std::shared_ptr<lang::Value>& value, CompileContext* context)
{
    definition_->setValue(value, context);
}