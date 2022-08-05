#include "Subscript.h"

#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"
#include "lang/statement/Statement.h"

Subscript::Subscript(std::unique_ptr<Expression> indexed, std::unique_ptr<Expression> index, lang::Location location)
    : Expression(location)
    , indexed_(std::move(indexed))
    , index_(std::move(index))
{
    addSubexpression(*indexed_);
    addSubexpression(*index_);
}

Expression& Subscript::indexed() const
{
    return *indexed_;
}

Expression& Subscript::index() const
{
    return *index_;
}

std::optional<lang::ResolvingHandle<lang::Type>> Subscript::tryGetType() const
{
    auto indexed_type_opt = indexed_->tryGetType();
    if (!indexed_type_opt) return std::nullopt;
    auto indexed_type = *indexed_type_opt;

    return indexed_type->getSubscriptReturnType();
}

bool Subscript::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    valid &= indexed_->validate(validation_logger);
    valid &= index_->validate(validation_logger);

    if (!valid) return false;

    lang::ResolvingHandle<lang::Type> indexed_type = indexed_->type();

    if (indexed_type->isSubscriptDefined())
    {
        return indexed_type->validateSubscript(indexed_->location(),
                                               index_->type(),
                                               index_->location(),
                                               validation_logger);
    }
    else {
        validation_logger.logError("Type " + indexed_type->getAnnotatedName() + " does not provide subscript",
                                   location());

        return false;
    }
}

Expression::Expansion Subscript::expandWith(Expressions subexpressions) const
{
    return {Statements(),
            std::make_unique<Subscript>(std::move(subexpressions[0]), std::move(subexpressions[1]), location()),
            Statements()};
}

void Subscript::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> return_value =
        indexed_->type()->buildSubscript(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

Subscript::~Subscript() = default;
