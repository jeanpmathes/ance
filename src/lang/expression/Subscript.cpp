#include "Subscript.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

Subscript::Subscript(Owned<Expression> indexed, Owned<Expression> index, lang::Location location)
    : Expression(location)
    , indexed_(std::move(indexed))
    , index_(std::move(index))
{
    addSubexpression(*indexed_);
    addSubexpression(*index_);
}

Expression const& Subscript::indexed() const
{
    return *indexed_;
}

Expression const& Subscript::index() const
{
    return *index_;
}

void Subscript::walkDefinitions()
{
    Expression::walkDefinitions();

    type();

    indexed_->type();
    index_->type();
}

void Subscript::defineType(lang::ResolvingHandle<lang::Type> type)
{
    auto indexed_type = indexed_->type();
    if (indexed_type->isDefined()) { type.reroute(indexed_type->getSubscriptReturnType()); }
}

bool Subscript::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    valid &= indexed_->validate(validation_logger);
    valid &= index_->validate(validation_logger);

    if (!valid) return false;

    lang::Type const& indexed_type = indexed_->type();
    if (!indexed_type.isDefined()) return false;

    if (indexed_type.isSubscriptDefined())
    {
        return indexed_type.validateSubscript(indexed_->location(),
                                              index_->type(),
                                              index_->location(),
                                              validation_logger);
    }
    else
    {
        validation_logger.logError("Type " + indexed_type.getAnnotatedName() + " does not provide subscript",
                                   location());

        return false;
    }
}

Expression::Expansion Subscript::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(),
            makeOwned<Subscript>(std::move(subexpressions[0]), std::move(subexpressions[1]), location()),
            Statements()};
}

Subscript::~Subscript() = default;
