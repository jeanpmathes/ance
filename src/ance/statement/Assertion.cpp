#include "Assertion.h"

#include "ance/construct/Function.h"
#include "ance/expression/Expression.h"
#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "validation/ValidationLogger.h"
#include "ance/type/Type.h"
#include "ance/type/IntegerType.h"

Assertion::Assertion(std::unique_ptr<Expression> condition, ance::Location location)
    : Statement(location)
    , condition_(std::move(condition))
{}

void Assertion::setFunction(ance::Function* function)
{
    condition_->setContainingScope(function);
}

void Assertion::validate(ValidationLogger& validation_logger)
{
    bool is_valid = condition_->validate(validation_logger);
    if (!is_valid) return;

    ance::Type::checkMismatch(ance::IntegerType::getBooleanType(),
                              condition_->type(),
                              condition_->location(),
                              validation_logger);
}

void Assertion::doBuild(CompileContext* context)
{
    context->runtime()->buildAssert(condition_->getValue(), context);
}
