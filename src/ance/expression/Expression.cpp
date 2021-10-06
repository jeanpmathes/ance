#include "Expression.h"

#include "ance/type/ReferenceType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

Expression::Expression(ance::Location location) : location_(location) {}

ance::Location Expression::location() const
{
    return location_;
}

ance::Scope* Expression::scope() const
{
    return containing_scope_;
}

void Expression::setContainingScope(ance::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void Expression::setScope(ance::Scope*) {}

bool Expression::isNamed()
{
    return ance::ReferenceType::isReferenceType(type());
}

bool Expression::validateAssignment(ance::Value*, ance::Location, ValidationLogger& validation_logger)
{
    validation_logger.logError("Cannot assign to this expression", location());

    return false;
}

void Expression::assign(ance::Value* value, ance::Location value_location, CompileContext* context)
{
    context->setDebugLocation(location(), containing_scope_);
    doAssign(value, value_location, context);
    context->resetDebugLocation();
}

void Expression::doAssign(ance::Value*, ance::Location, CompileContext*) {}
