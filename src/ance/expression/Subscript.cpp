#include "Subscript.h"

#include "ance/type/Type.h"
#include "validation/ValidationLogger.h"

Subscript::Subscript(std::unique_ptr<Expression> indexed, std::unique_ptr<Expression> index, ance::Location location)
    : Expression(location)
    , indexed_(std::move(indexed))
    , index_(std::move(index))
{}

void Subscript::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

ance::ResolvingHandle<ance::Type> Subscript::type()
{
    return indexed_->type()->getSubscriptReturnType();
}

bool Subscript::validate(ValidationLogger& validation_logger)
{
    bool valid = true;

    valid &= indexed_->validate(validation_logger);
    valid &= index_->validate(validation_logger);

    if (!valid) return false;

    ance::ResolvingHandle<ance::Type> indexed_type = indexed_->type();

    if (indexed_type->isSubscriptDefined())
    {
        return indexed_type->validateSubscript(indexed_->location(),
                                               index_->type(),
                                               index_->location(),
                                               validation_logger);
    }
    else
    {
        validation_logger.logError("Type " + indexed_type->getAnnotatedName() + " does not provide get indexer",
                                   location());

        return false;
    }
}

void Subscript::doBuild(CompileContext* context)
{
    std::shared_ptr<ance::Value> return_value =
        indexed_->type()->buildSubscript(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

Subscript::~Subscript() = default;
