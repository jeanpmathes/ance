#include "Expression.h"

#include "ance/construct/value/Value.h"
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

bool Expression::validateAssignment(ance::Value*      value,
                                    ance::Location    value_location,
                                    ValidationLogger& validation_logger)
{
    if (ance::ReferenceType::isReferenceType(type()))
    {
        ance::Type* target_type = ance::ReferenceType::getReferencedType(type());
        return ance::Type::checkMismatch(target_type, value->type(), value_location, validation_logger);
    }
    else
    {
        validation_logger.logError("Cannot assign to this expression", location());
        return false;
    }
}

void Expression::assign(ance::Value* value, CompileContext* context)
{
    context->setDebugLocation(location(), containing_scope_);
    doAssign(value, context);
    context->resetDebugLocation();
}

void Expression::doAssign(ance::Value* value, CompileContext* context)
{
    assert(ance::ReferenceType::isReferenceType(type()));

    ance::Type* target_type = ance::ReferenceType::getReferencedType(type());
    value                   = ance::Type::makeMatching(target_type, value, context);

    ance::Value* expression_return = getValue();

    expression_return->buildContentValue(context);
    value->buildContentValue(context);

    context->ir()->CreateStore(value->getContentValue(), expression_return->getContentValue());
}
