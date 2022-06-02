#include "BindRef.h"

#include "lang/expression/Addressof.h"
#include "lang/type/PointerType.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"
#include "lang/expression/BindRefTo.h"

BindRef::BindRef(std::unique_ptr<Expression> value, lang::Location location)
    : UnexpandedExpression(location)
    , value_(std::move(value))
{
    addSubexpression(*value_);
}

Expression& BindRef::value() const
{
    return *value_;
}

lang::ResolvingHandle<lang::Type> BindRef::type()
{
    if (!type_)
    {
        lang::ResolvingHandle<lang::Type> element_type = value_->type();

        if (element_type->isReferenceType()) { element_type = element_type->getElementType(); }

        type_ = lang::ReferenceType::get(element_type);
    }

    return *type_;
}

bool BindRef::validate(ValidationLogger& validation_logger)
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

Expression::Expansion BindRef::expandWith(Expressions subexpressions) const
{
    return {
        Statements(),
        std::make_unique<BindRefTo>(std::make_unique<Addressof>(std::move(subexpressions[0]), location()), location()),
        Statements()};
}

BindRef::~BindRef() = default;
