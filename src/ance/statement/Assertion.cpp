#include "Assertion.h"

#include "ance/construct/Function.h"
#include "ance/expression/Expression.h"
#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"

Assertion::Assertion(std::unique_ptr<Expression> condition, ance::Location location)
    : Statement(location)
    , condition_(std::move(condition))
{}

void Assertion::setFunction(ance::Function* function)
{
    condition_->setContainingScope(function);
}

void Assertion::validate(ValidationLogger& validation_logger) {}

void Assertion::doBuild(CompileContext* context)
{
    context->runtime()->buildAssert(condition_->getValue(), context);
}
