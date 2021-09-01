#include "IndexerSet.h"

IndexerSet::IndexerSet(Expression* indexed, Expression* index, ance::Location location)
    : Assignable(location)
    , indexed_(indexed)
    , index_(index)
{}

void IndexerSet::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

void IndexerSet::validate(ValidationLogger& validation_logger)
{
    indexed_->validate(validation_logger);
    index_->validate(validation_logger);

    ance::Type* indexed_type = indexed_->type();

    if (indexed_type->isIndexerDefined(Indexer::SET))
    {
        indexed_type->validateSetIndexer(indexed_->getValue(),
                                         indexed_->location(),
                                         index_->getValue(),
                                         index_->location(),
                                         assigned(),
                                         assignedLocation(),
                                         validation_logger);
    }
    else
    {
        validation_logger.logError("Type '" + indexed_type->getName() + "' does not provide set indexer", location());
    }
}

void IndexerSet::doBuild(CompileContext* context)
{
    indexed_->type()->buildSetIndexer(indexed_->getValue(), index_->getValue(), assigned(), context);
}
