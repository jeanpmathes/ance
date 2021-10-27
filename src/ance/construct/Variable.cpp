#include "Variable.h"

#include <utility>

#include "ance/construct/LocalVariable.h"
#include "ance/construct/Parameter.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/ReferenceType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Variable::Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_final)
    : identifier_(std::move(identifier))
    , is_defined_(true)
    , scope_(containing_scope)
    , type_(type)
    , is_final_(is_final)
{}

ance::Variable::Variable(std::string identifier)
    : identifier_(std::move(identifier))
    , is_defined_(false)
    , scope_(nullptr)
    , type_(nullptr)
    , is_final_(true)
{}

void ance::Variable::define(ance::Scope* containing_scope, ance::Type* type, bool is_final)
{
    assert(!is_defined_);

    scope_    = containing_scope;
    type_     = type;
    is_final_ = is_final;

    is_defined_ = true;
}

bool ance::Variable::isDefined() const
{
    return is_defined_;
}

std::string ance::Variable::identifier() const
{
    return identifier_;
}

ance::Scope* ance::Variable::scope() const
{
    assert(is_defined_);
    return scope_;
}

ance::Type* ance::Variable::type() const
{
    assert(is_defined_);
    return type_;
}

bool ance::Variable::isFinal() const
{
    assert(is_defined_);
    return is_final_;
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

    ance::Type* target_type = type();

    if (ance::ReferenceType::isReferenceType(type())) { target_type = ance::ReferenceType::getReferencedType(type()); }

    ance::Type::checkMismatch(target_type, value->type(), assigned_location, validation_logger);
}
void ance::Variable::setValue(const std::shared_ptr<ance::Value>& value, CompileContext* context)
{
    if (ance::ReferenceType::isReferenceType(type()))
    {
        std::shared_ptr<ance::Value> reference = getValue(context);

        reference->buildContentValue(context);
        value->buildContentValue(context);

        context->ir()->CreateStore(value->getContentValue(), reference->getContentValue());
    }
    else
    {
        storeValue(value, context);
    }
}
