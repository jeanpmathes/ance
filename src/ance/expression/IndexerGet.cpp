#include "IndexerGet.h"

#include "ance/type/Type.h"

IndexerGet::IndexerGet(Expression* indexed, Expression* index, ance::Location location)
    : Expression(location)
    , indexed_(indexed)
    , index_(index)
{
    addChild(*index);
    addChild(*indexed);
}

void IndexerGet::setScope(ance::Scope* scope)
{
    indexed_->setContainingScope(scope);
    index_->setContainingScope(scope);
}

ance::Type* IndexerGet::type()
{
    return indexed_->type()->getIndexerReturnType();
}

bool IndexerGet::validate(ValidationLogger& validation_logger)
{
    indexed_->validate(validation_logger);
    index_->validate(validation_logger);

    ance::Type* indexed_type = indexed_->type();

    if (indexed_type->isIndexerDefined(Indexer::GET))
    {
        return indexed_type->validateGetIndexer(indexed_->getValue(),
                                                indexed_->location(),
                                                index_->getValue(),
                                                index_->location(),
                                                validation_logger);
    }
    else
    {
        validation_logger.logError("Type '" + indexed_type->getName() + "' does not provide get indexer", location());

        return false;
    }
}

void IndexerGet::doBuild(CompileContext* context)
{
    ance::Value* return_value = indexed_->type()->buildGetIndexer(indexed_->getValue(), index_->getValue(), context);
    setValue(return_value);
}

bool IndexerGet::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitIndexerGet(*this);
}

IndexerGet::~IndexerGet() = default;
