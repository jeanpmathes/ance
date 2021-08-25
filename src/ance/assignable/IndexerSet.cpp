#include "IndexerSet.h"

IndexerSet::IndexerSet(Expression* indexed, Expression* index) : indexed_(indexed), index_(index) {}

void IndexerSet::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

void IndexerSet::assign(ance::Value* value, CompileContext* context)
{
    ance::Type* indexed_type = indexed_->type();
    assert(indexed_type->isIndexerDefined(Indexer::SET) && "Type does not support this indexer.");

    indexed_type->buildSetIndexer(indexed_->getValue(), index_->getValue(), value, context);
}
