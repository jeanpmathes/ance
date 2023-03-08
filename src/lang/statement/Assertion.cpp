#include "Assertion.h"

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

Assertion::Assertion(Owned<Expression> condition, lang::Location location)
    : Statement(location)
    , condition_(std::move(condition))
{
    addSubexpression(*condition_);
}

Expression const& Assertion::condition() const
{
    return *condition_;
}

void Assertion::validate(ValidationLogger& validation_logger) const
{
    bool const is_valid = condition_->validate(validation_logger);
    if (!is_valid) return;

    lang::Type::checkMismatch(scope()->context().getBooleanType(),
                              condition_->type(),
                              condition_->location(),
                              validation_logger);

    scope()->context().validateRuntimeDependency(location(), validation_logger);
}

Statements Assertion::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Assertion>(std::move(subexpressions[0]), location()));

    return statements;
}

void Assertion::doBuild(CompileContext& context)
{
    context.runtime().buildAssert(condition_->getValue(),
                                  "Assertion failed at " + context.getLocationString(),
                                  context);
}
