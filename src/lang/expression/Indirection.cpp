#include "Indirection.h"

#include "lang/statement/Statement.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

Indirection::Indirection(std::unique_ptr<Expression> expression, lang::Location location)
    : Expression(location)
    , value_(std::move(expression))

{
    addSubexpression(*value_);
}

Expression& Indirection::value() const
{
    return *value_;
}

std::optional<lang::ResolvingHandle<lang::Type>> Indirection::tryGetType() const
{
    auto type_opt = value_->tryGetType();
    if (!type_opt) return std::nullopt;
    auto type = type_opt.value();

    return lang::ReferenceType::get(type->getIndirectionType());
}

bool Indirection::validate(ValidationLogger& validation_logger) const
{
    if (!value_->validate(validation_logger)) return false;

    if (!value_->type()->definesIndirection())
    {
        validation_logger.logError("Type " + value_->type()->getAnnotatedName() + " does not define indirection",
                                   location());
        return false;
    }

    return value_->type()->validateIndirection(location(), validation_logger);
}

Expression::Expansion Indirection::expandWith(Expressions subexpressions) const
{
    return {Statements(), std::make_unique<Indirection>(std::move(subexpressions[0]), location()), Statements()};
}

void Indirection::doBuild(CompileContext& context)
{
    std::shared_ptr<lang::Value> ref = value_->type()->buildIndirection(value_->getValue(), context);
    setValue(ref);
}

Indirection::~Indirection() = default;
