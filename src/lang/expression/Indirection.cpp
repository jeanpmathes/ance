#include "Indirection.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

Indirection::Indirection(Owned<Expression> expression, lang::Location location)
    : Expression(location)
    , value_(std::move(expression))

{
    addSubexpression(*value_);
}

Expression const& Indirection::value() const
{
    return *value_;
}

void Indirection::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    auto value_type = value_->type();

    if (value_type->isDefined())
    {
        type.reroute(scope()->context().getReferenceType(value_type->getIndirectionType()));
    }
}

bool Indirection::validate(ValidationLogger& validation_logger) const
{
    if (!value_->validate(validation_logger)) return false;

    if (!value_->type().definesIndirection())
    {
        validation_logger.logError("Type " + value_->type().getAnnotatedName() + " does not define indirection",
                                   location());
        return false;
    }

    return value_->type().validateIndirection(location(), validation_logger);
}

Expression::Expansion Indirection::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<Indirection>(std::move(subexpressions[0]), location()), Statements()};
}

void Indirection::doBuild(CompileContext& context)
{
    Shared<lang::Value> ref = value_->type()->buildIndirection(value_->getValue(), context);
    setValue(ref);
}

Indirection::~Indirection() = default;
