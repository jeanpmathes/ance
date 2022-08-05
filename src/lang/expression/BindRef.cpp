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

std::optional<lang::ResolvingHandle<lang::Type>> BindRef::tryGetType() const
{
    auto element_type_opt = value_->tryGetType();
    if (!element_type_opt) return std::nullopt;
    auto element_type = *element_type_opt;

    if (element_type->isReferenceType()) { element_type = element_type->getElementType(); }

    return lang::ReferenceType::get(element_type);
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

Expression::Expansion BindRef::expandWith(Expressions subexpressions) const
{
    return {
        Statements(),
        std::make_unique<BindRefTo>(std::make_unique<Addressof>(std::move(subexpressions[0]), location()), location()),
        Statements()};
}

BindRef::~BindRef() = default;
