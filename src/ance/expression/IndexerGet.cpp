#include "IndexerGet.h"

#include "ance/type/Type.h"

IndexerGet::IndexerGet(Expression* indexed, Expression* index, ance::Location location)
    : DelayableExpression(location)
    , indexed_(indexed)
    , index_(index)
{}

void IndexerGet::setScope(ance::Scope* scope)
{
    indexed_->setScope(scope);
    index_->setScope(scope);
}

ance::Type* IndexerGet::type()
{
    return indexed_->type()->getIndexerReturnType();
}

void IndexerGet::buildValue(CompileContext* context)
{
    ance::Type* indexed_type = indexed_->type();
    assert(indexed_type->isIndexerDefined(Indexer::GET) && "Type does not support this indexer.");

    ance::Value* return_value = indexed_type->buildGetIndexer(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

IndexerGet::~IndexerGet() = default;
