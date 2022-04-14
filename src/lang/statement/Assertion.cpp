#include "Assertion.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "validation/ValidationLogger.h"
#include "lang/type/Type.h"
#include "lang/type/BooleanType.h"

Assertion::Assertion(std::unique_ptr<Expression> condition, lang::Location location)
    : Statement(location)
    , condition_(std::move(condition))
{
    addSubexpression(*condition_);
}

Expression& Assertion::condition() const
{
    return *condition_;
}

void Assertion::validate(ValidationLogger& validation_logger)
{
    bool is_valid = condition_->validate(validation_logger);
    if (!is_valid) return;

    lang::Type::checkMismatch(lang::BooleanType::get(), condition_->type(), condition_->location(), validation_logger);
}

void Assertion::doBuild(CompileContext* context)
{
    context->runtime()->buildAssert(condition_->getValue(), context);
}
