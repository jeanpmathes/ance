#include "Expression.h"

#include <utility>

#include "lang/construct/value/Value.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/Type.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

Expression::Expression(lang::Location location) : location_(location) {}

lang::Location Expression::location() const
{
    return location_;
}

lang::Scope* Expression::scope() const
{
    return containing_scope_;
}

void Expression::setContainingScope(lang::Scope* scope)
{
    containing_scope_ = scope;
    setScope(scope);
}

void Expression::setScope(lang::Scope*) {}

bool Expression::isNamed()
{
    return type()->isReferenceType();
}

bool Expression::validateAssignment(const std::shared_ptr<lang::Value>& value,
                                    lang::Location                      value_location,
                                    ValidationLogger&                   validation_logger)
{
    if (type()->isReferenceType())
    {
        lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
        return lang::Type::checkMismatch(target_type, value->type(), value_location, validation_logger);
    }
    else {
        validation_logger.logError("Cannot assign to this expression", location());
        return false;
    }
}

void Expression::assign(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    context->setDebugLocation(location(), containing_scope_);
    doAssign(std::move(value), context);
    context->resetDebugLocation();
}

void Expression::doAssign(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    assert(type()->isReferenceType());

    lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
    value                                         = lang::Type::makeMatching(target_type, value, context);

    std::shared_ptr<lang::Value> expression_return = getValue();

    expression_return->buildContentValue(context);
    value->buildContentValue(context);

    context->ir()->CreateStore(value->getContentValue(), expression_return->getContentValue());
}
