#include "BindRef.h"

#include "lang/ApplicationVisitor.h"
#include "lang/expression/Addressof.h"
#include "lang/expression/BindRefTo.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

BindRef::BindRef(Owned<Expression> value, lang::Location location)
    : UnexpandedExpression(location)
    , value_(std::move(value))
{
    addSubexpression(*value_);
}

Expression const& BindRef::value() const
{
    return *value_;
}

void BindRef::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    auto element_type = value_->type();

    if (element_type->isDefined())
    {
        if (element_type->isReferenceType()) { element_type = element_type->getElementType(); }

        type.reroute(scope()->context().getReferenceType(element_type));
    }
}

bool BindRef::validate(ValidationLogger& validation_logger) const
{
    bool is_arg_valid = value_->validate(validation_logger);
    if (!is_arg_valid) return false;

    if (!value_->isNamed())
    {
        validation_logger.logError("Cannot get address of unnamed value", value_->location());
        return false;
    }

    return true;
}

Expression::Expansion BindRef::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(),
            makeOwned<BindRefTo>(makeOwned<Addressof>(std::move(subexpressions[0]), location()), location()),
            Statements()};
}

BindRef::~BindRef() = default;
