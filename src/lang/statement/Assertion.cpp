#include "Assertion.h"

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

bool Assertion::validate(ValidationLogger& validation_logger) const
{
    bool is_valid = condition_->validate(validation_logger);
    if (!is_valid) return false;

    is_valid &= lang::Type::checkMismatch(scope().context().getBooleanType(),
                                          condition_->type(),
                              condition_->location(),
                              validation_logger);

    is_valid &= scope().context().validateRuntimeDependency(location(), validation_logger);

    return is_valid;
}

Statements Assertion::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Assertion>(std::move(subexpressions[0]), location()));

    return statements;
}
