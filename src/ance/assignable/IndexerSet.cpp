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

void IndexerSet::buildAssignment(ance::Value* value, CompileContext* context)
{
    ance::Type* indexed_type = indexed_->type();
    assert(indexed_type->isIndexerDefined(Indexer::SET) && "Type does not support this indexer.");

    indexed_type->buildSetIndexer(indexed_->getValue(), index_->getValue(), value, context);
}
