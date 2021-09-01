#include "IndexerGet.h"

#include "ance/type/Type.h"

IndexerGet::IndexerGet(Expression* indexed, Expression* index, ance::Location location)
    : Expression(location)
    , indexed_(indexed)
    , index_(index)
{}

void IndexerGet::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

ance::Type* IndexerGet::type()
{
    return indexed_->type()->getIndexerReturnType();
}

void IndexerGet::validate(ValidationLogger& validation_logger)
{
    indexed_->validate(validation_logger);
    index_->validate(validation_logger);

    ance::Type* indexed_type = indexed_->type();
    assert(indexed_type->isIndexerDefined(Indexer::GET) && "Type does not support this indexer.");

    indexed_type->validateGetIndexer(indexed_->getValue(), index_->getValue(), validation_logger);
}

void IndexerGet::doBuild(CompileContext* context)
{
    ance::Value* return_value = indexed_->type()->buildGetIndexer(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

IndexerGet::~IndexerGet() = default;
