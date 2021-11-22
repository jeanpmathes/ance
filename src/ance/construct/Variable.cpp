#include "Variable.h"

#include <utility>

#include "ance/construct/GlobalVariable.h"
#include "ance/construct/LocalVariable.h"
#include "ance/construct/Parameter.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/Type.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Variable::Variable(std::string identifier) : identifier_(std::move(identifier)) {}

bool ance::Variable::isDefined() const
{
    return (definition_ != nullptr);
}

void ance::Variable::defineAsGlobal(ance::ResolvingHandle<ance::Type> type,
                                    ance::Location                    type_location,
                                    ance::GlobalScope*                containing_scope,
                                    AccessModifier                    access,
                                    ConstantExpression*               constant_init,
                                    bool                              is_final,
                                    bool                              is_constant,
                                    ance::Location                    location)
{
    definition_ = std::make_unique<ance::GlobalVariable>(identifier(),
                                                         type,
                                                         type_location,
                                                         containing_scope,
                                                         access,
                                                         constant_init,
                                                         is_final,
                                                         is_constant,
                                                         location);
}

void ance::Variable::defineAsLocal(ance::ResolvingHandle<ance::Type>   type,
                                   ance::Location                      type_location,
                                   ance::LocalScope*                   containing_scope,
                                   bool                                is_final,
                                   const std::shared_ptr<ance::Value>& value,
                                   unsigned int                        parameter_no,
                                   ance::Location                      location)
{
    definition_ = std::make_unique<ance::LocalVariable>(identifier(),
                                                        type,
                                                        type_location,
                                                        containing_scope,
                                                        is_final,
                                                        value,
                                                        parameter_no,
                                                        location);
}

const std::string& ance::Variable::identifier() const
{
    return identifier_;
}

ance::Scope* ance::Variable::scope() const
{
    assert(definition_);
    return definition_->scope();
}

ance::ResolvingHandle<ance::Type> ance::Variable::type() const
{
    assert(definition_);
    return definition_->type();
}

bool ance::Variable::isFinal() const
{
    assert(definition_);
    return definition_->isFinal();
}

void ance::Variable::validate(ValidationLogger& validation_logger)
{
    definition_->validate(validation_logger);
}

void ance::Variable::buildDeclaration(CompileContext* context)
{
    definition_->buildDeclaration(context);
}

void ance::Variable::buildDefinition(CompileContext* context)
{
    definition_->buildDefinition(context);
}

bool ance::Variable::validateGetValue(ValidationLogger& validation_logger, ance::Location location) const
{
    if (!isDefined())
    {
        validation_logger.logError("Name '" + identifier() + "' not defined in the current context", location);
        return false;
    }

    return true;
}

void ance::Variable::validateSetValue(const std::shared_ptr<ance::Value>& value,
                                      ValidationLogger&                   validation_logger,
                                      ance::Location                      assignable_location,
                                      ance::Location                      assigned_location) const
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

    ance::ResolvingHandle<ance::Type> target_type = type();

    if (ance::ReferenceType::isReferenceType(type())) { target_type = ance::ReferenceType::getReferencedType(type()); }

    ance::Type::checkMismatch(target_type, value->type(), assigned_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::Variable::getValue(CompileContext* context)
{
    return definition_->getValue(context);
}

void ance::Variable::setValue(const std::shared_ptr<ance::Value>& value, CompileContext* context)
{
    definition_->setValue(value, context);
}
